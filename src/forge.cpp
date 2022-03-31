#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <eosio/system.hpp>

using namespace eosio;

class[[eosio::contract]] forge : public eosio::contract {

  public:

    using contract::contract;

    [[eosio::on_notify("eosio.token::transfer")]] void received(const eosio::name caller, eosio::name receiver, eosio::asset value, std::string memo) {
      // Validate transaction participants and escape
      if (receiver != get_self() || caller == get_self()) return;
      // Define token symbol
      eosio::symbol token_symbol("TUB", 0);
      // Validate contract state and arguments
      eosio::check(value.amount > 0, "Insufficient value");
      eosio::check(value.symbol == token_symbol, "Illegal asset symbol");
      
      // Find the members wallet
      wallet_table balances(get_self(), get_self().value);
      auto wallet = balances.find(caller.value);
      // Update the wallet balance
      if (wallet != balances.end()) {
        balances.modify(wallet, get_self(), [&](auto &row) {
          row.balance += value.amount;
        });
      } else {
        balances.emplace(get_self(), [&](auto &row) {
          row.account = caller;
          row.balance = value.amount;
        });
      }

      
      license_table licenses(get_self(), get_self().value);
      auto licence = licenses.find(caller.value);
      
      if (licence != licenses.end()) {
        licenses.modify(licence, get_self(), [&](auto &row) {
          row.endate +=2592000;
        });
      } else {
        licenses.emplace(get_self(), [&](auto &row) {
          row.account = caller;
          row.endate = (current_time_point().sec_since_epoch()+2592000);
        });
      }
    }

  private:
    struct [[eosio::table]] WalletStruct {
      name          account;
      uint64_t      balance = 0;
      auto primary_key() const { return account.value; }
    };
    typedef multi_index<"wallets"_n, WalletStruct> wallet_table;

    struct [[eosio::table]] LicenseStruct {
      name          account;
      uint32_t      endate = 0;
      auto primary_key() const { return account.value; }
    };

    typedef multi_index<"licenses"_n, LicenseStruct> license_table;
};