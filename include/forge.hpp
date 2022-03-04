#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <eosio/asset.hpp>
#include <eosio/system.hpp>

using namespace std;
using namespace eosio;

CONTRACT forge : public contract {
  public:
    using contract::contract;
    ACTION getlicense(name registree,string type);
    private:
      TABLE licenses {
        name  user;
        uint32_t enddate ;
        auto primary_key() const {return user.value;}
      };
    
      typedef multi_index<name("licenses"),licenses>licenses_table;

  
};
