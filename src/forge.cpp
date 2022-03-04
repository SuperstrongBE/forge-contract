#include <forge.hpp>
#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <eosio/asset.hpp>
#include <eosio/system.hpp>

using namespace eosio;

ACTION forge::getlicense(name registree, string type) {
  // Check fo user auth
  check(has_auth(registree),"This user not exists");
  //A line to force build
  //Pay for license
  action(
        permission_level{registree,"active"_n},
        "xtokens"_n,
        "transfer"_n,
        std::make_tuple(get_self(),registree, asset{ 10, symbol{"USDT", 6}} , std::string("money in your pocket !"))
         ).send();

  //Init licenses table
  licenses_table _licenses(get_self(),get_self().value);
  auto lsc_itr = _licenses.find(registree.value);

  if (lsc_itr == _licenses.end()) {
    // Create a record user dont own a license
    _licenses.emplace(registree, [&](auto& license) {
      license.user = registree;
      license.enddate = (current_time_point().sec_since_epoch()+2592000); 

    });
  } else {
    // extends license user if exist
    _licenses.modify(lsc_itr, registree, [&](auto& license) {
      license.enddate +=+2592000;
    });
  }
}

EOSIO_DISPATCH(forge, (getlicense))
