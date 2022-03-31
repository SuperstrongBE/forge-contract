#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <eosio/asset.hpp>
#include <eosio/system.hpp>

using namespace std;
using namespace eosio;

CONTRACT forge : public contract {
 
    private:
 struct [[eosio::table]] WalletStruct {
      name          account;
      uint64_t      balance = 0;
      auto primary_key() const { return account.value; }
    };
    typedef multi_index<"wallets"_n, WalletStruct> wallet_table;

    struct [[eosio::table]] LicenseStruct {
      name          account;
      uint64_t      endate = 0;
      auto primary_key() const { return account.value; }
    };

    typedef multi_index<"licenses"_n, LicenseStruct> license_table;
  
};