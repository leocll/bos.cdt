#include <eosiolib/name.hpp>
#include <eosiolib/action.hpp>
#include "../intrinsics.hpp"
#include <cstdint>
#include <functional>
#include <stdio.h>
#include <setjmp.h>

eosio::native::intrinsics __intrins;

extern "C" {
   int main(int, char**);
   char* _mmap();
   
   static jmp_buf ___env;
   static jmp_buf ___test_env;
   static int ___jmp_ret;
   static int ___test_ret;
   jmp_buf* ___test_env_ptr = &___test_env;
   int*     ___test_ret_ptr = &___test_ret;
   char* ___heap;
   char* ___heap_ptr;
   void ___putc(char c);
   void prints_l(const char* cstr, uint32_t len) {
      for (int i=0; i < len; i++)
         ___putc(cstr[i]);
   }

   void prints(const char* cstr) {
      for (int i=0; cstr[i] != '\0'; i++)
         ___putc(cstr[i]);
   }

   void printi(int64_t value) {
      printf("%lli\n", value);
   }

   void printui(uint64_t value) {
      printf("%llu\n", value);
   }
   
   void printi128(const int128_t* value) {
      int* tmp = (int*)value;
      printf("0x%04x%04x%04x%04x\n", tmp[0], tmp[1], tmp[2], tmp[3]);
   }

    void printui128(const uint128_t* value) {
      int* tmp = (int*)value;
      printf("0x%04x%04x%04x%04x\n", tmp[0], tmp[1], tmp[2], tmp[3]);
   }
  
   void printsf(float value) {
      printf("%f\n", value);
   }

   void printdf(double value) {
      printf("%f\n", value);
   }

   void printqf(const long double* value) {
      int* tmp = (int*)value;
      printf("0x%04x%04x%04x%04x\n", tmp[0], tmp[1], tmp[2], tmp[3]);
   }
   
   void printn(uint64_t nm) {
      std::string s = eosio::name(nm).to_string();
      prints_l(s.c_str(), s.length());
   }
   
   void printhex(const void* data, uint32_t len) {
   }

   void* memset ( void* ptr, int value, size_t num ) {
      unsigned char v = value;
      char* _ptr = (char*)ptr;
      for (int i=0; i < num; i++) {
         _ptr[i] = v;
      }
      return (void*)_ptr;
   }

   void* memcpy ( void* destination, const void* source, size_t num ) {
      char* dest = (char*)destination;
      char* src = (char*)source;
      for (int i=0; i < num; i++) {
         dest[i] = src[i];
      }
      return (void*)dest;
   }

   void* memmove ( void* destination, const void* source, size_t num ) {
      char tmp_buf[num];
      char* dest = (char*)destination;
      char* src = (char*)source;
      for (int i=0; i < num; i++)
         tmp_buf[i] = src[i];
      for (int i=0; i < num; i++)
         dest[i] = tmp_buf[i];
      return (void*)dest;
   }

   void eosio_assert(uint32_t test, const char* msg) {
      if (test == 0) {
         //prints("asserted with message [");
         prints(msg);
         prints_l("\n", 1);
         longjmp(___env, 1);
      }
   }

   void eosio_assert_message(uint32_t test, const char* msg, uint32_t len) {
      if (test == 0) {
         //prints("asserted with message [");
         prints_l(msg, len);
         prints_l("\n", 1);
         longjmp(___env, 1);
      }
   }

   void eosio_assert_code(uint32_t test, uint64_t code) {
      if (test == 0) {
         //prints("asserted with code [");
         printui(code);
         prints_l("\n", 1);
         longjmp(___env, 1);
      }
   }
   
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-noreturn" 
   void abort() {
      eosio_assert(false, "abort");
   }
#pragma clang diagnostic pop
   
   bool is_feature_active( int64_t feature ) {
      return __intrins.call<eosio::native::intrinsic_is_feature_active>(feature);
   }
   void set_blockchain_parameters_packed( char* data, uint32_t datalen ){}
   void get_blockchain_parameters_packed( char* data, uint32_t datalen ){}

   size_t __builtin_wasm_current_memory() {
      return (size_t)___heap_ptr;
   }

   size_t __builtin_wasm_grow_memory(size_t size) {
      if ((___heap_ptr + (size*64*1024)) > (___heap_ptr + 100*1024*1024))
         eosio_assert(false, "__builtin_wasm_grow_memory");
      ___heap_ptr += (size*64*1024);
      return (size_t)___heap_ptr;
   }

   int _wrap_main(int argc, char** argv) {
      int ret_val = 0;
      ___heap = _mmap();
      ___heap_ptr = ___heap;
      ___test_ret = 1;
      ___jmp_ret = setjmp(___env); 
      if (___jmp_ret == 0) {
         ret_val = main(argc, argv);
      } else if (___jmp_ret == 1){
         if (___test_ret == 0)
            longjmp(___test_env,1);
         ret_val = -1;
         //longjmp(___env,2);
      }
      return ret_val;
   }

   // action.h
   uint32_t read_action_data( void* msg, uint32_t len ) {
      eosio_assert(false, "unsupported");
   }
   uint32_t action_data_size() {
      eosio_assert(false, "unsupported");
   }
   void require_recipient( capi_name name ) {
      eosio_assert(false, "unsupported");
   }
   void require_auth( capi_name name ) {
      eosio_assert(false, "unsupported");
   }
   bool has_auth( capi_name name ) {
      eosio_assert(false, "unsupported");
   }
   void require_auth2( capi_name name, capi_name permission ) {
      eosio_assert(false, "unsupported");
   }
   bool is_account( capi_name name ) {
      eosio_assert(false, "unsupported");
   }
   void send_inline(char *serialized_action, size_t size) {
      eosio_assert(false, "unsupported");
   }
   void send_context_free_inline(char *serialized_action, size_t size) {
      eosio_assert(false, "unsupported");
   }
   uint64_t  publication_time() {
      eosio_assert(false, "unsupported");
   }
   capi_name current_receiver() {
      eosio_assert(false, "unsupported");
   }
   
   // chain.h
   uint32_t get_active_producers( capi_name* producers, uint32_t datalen ) {
      eosio_assert(false, "unsupported");
   }
}