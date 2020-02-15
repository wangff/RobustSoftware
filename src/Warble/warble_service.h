#ifndef CSCI499_FEI_SRC_WARBLE_WARBLE_SERVICE_H_
#define CSCI499_FEI_SRC_WARBLE_WARBLE_SERVICE_H_

#include <memory>
#include <string>

#include <gtest/gtest_prod.h>

#include "../Func/storage_abstraction.h"
#include "profile.h"

using StoragePtr = std::shared_ptr<StorageAbstraction>;
using StringVector = std::vector<std::string>;
using StringOptional = std::optional<std::string>;
using StringOptionalVector = std::vector<StringOptional>;

// Warble application: a collection of handler functions to process users requests
class Warble {
 public:
  // Definition of all of keys' prefix
  std::string user_prefix = "user_";
  std::string user_warbles_prefix = "user_warbles_";
  std::string user_followers_prefix = "user_followers_";
  std::string user_followings_prefix = "user_followings_";
  std::string warble_prefix = "warble_";
  std::string warble_thread_prefix = "warble_thread_";

  // Constructor with the parameter of StoragePtr.
  // StoragePtr used by Warble to communicate with KeyValueStore.
  Warble(const StoragePtr &storage_ptr) : kv_store_(storage_ptr) {};

  // Register the given user_name
  bool RegisterUser(const std::string &user_name);

  // Post a new warble or post a new warble as a reply,
  // and return the id of the new warble.
  std::string WarbleText(const std::string &user_name, const std::string &text, const StringOptional &reply_to);
  //Start following a given user
  void Follow(const std::string &user_name, const std::string &to_follow);

  // TODO
  // Read a warble thread from the given id
  std::vector<std::string> ReadThread(const std::string &warble_id);

  // Return the given user's following and followers
  Profile ReadProfile(const std::string &user_name);

 private:
  // Pointer of storage abstraction.
  // Used to access the KeyValue storage.
  StoragePtr kv_store_;
};

#endif //CSCI499_FEI_SRC_WARBLE_WARBLE_SERVICE_H_