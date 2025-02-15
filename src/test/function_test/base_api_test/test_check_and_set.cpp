/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

// IWYU pragma: no_include <gtest/gtest-message.h>
// IWYU pragma: no_include <gtest/gtest-test-part.h>
#include <gtest/gtest.h>
#include <string>

#include "include/pegasus/client.h"
#include "pegasus/error.h"
#include "test/function_test/utils/test_util.h"

using namespace ::pegasus;

class check_and_set : public test_util
{
};

TEST_F(check_and_set, value_not_exist)
{
    std::string hash_key("check_and_set_test_value_not_exist");

    {
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_NOT_EXIST,
                                         "",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_FALSE(results.check_value_exist);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v1", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_NOT_EXIST,
                                         "",
                                         "k1",
                                         "v2",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v1", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v1", value);

        options.return_check_value = false;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_NOT_EXIST,
                                         "",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_FALSE(results.check_value_returned);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v1", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));
    }

    {
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k2"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k2",
                                         pegasus_client::cas_check_type::CT_VALUE_NOT_EXIST,
                                         "",
                                         "k2",
                                         "",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_FALSE(results.check_value_exist);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k2", value));
        ASSERT_EQ("", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k2",
                                         pegasus_client::cas_check_type::CT_VALUE_NOT_EXIST,
                                         "",
                                         "k2",
                                         "v2",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k2", value));
        ASSERT_EQ("", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k2"));
    }

    {
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k3"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k3",
                                         pegasus_client::cas_check_type::CT_VALUE_NOT_EXIST,
                                         "",
                                         "k4",
                                         "v4",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_FALSE(results.check_value_exist);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k4", value));
        ASSERT_EQ("v4", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k3"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));
    }
}

TEST_F(check_and_set, value_exist)
{
    std::string hash_key("check_and_set_test_value_exist");

    {
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_EXIST,
                                         "",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_FALSE(results.check_value_exist);
        ASSERT_EQ(PERR_NOT_FOUND, client_->get(hash_key, "k1", value));

        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k1", ""));

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_EXIST,
                                         "",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v1", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_EXIST,
                                         "",
                                         "k1",
                                         "v2",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v1", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));
    }

    {
        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k3", "v3"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k3",
                                         pegasus_client::cas_check_type::CT_VALUE_EXIST,
                                         "",
                                         "k4",
                                         "v4",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v3", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k4", value));
        ASSERT_EQ("v4", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k3"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));
    }
}

TEST_F(check_and_set, value_not_empty)
{
    std::string hash_key("check_and_set_test_value_not_empty");

    {
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_NOT_EMPTY,
                                         "",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_FALSE(results.check_value_exist);
        ASSERT_EQ(PERR_NOT_FOUND, client_->get(hash_key, "k1", value));

        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k1", ""));

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_NOT_EMPTY,
                                         "",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("", value);

        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k1", "v1"));

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_NOT_EMPTY,
                                         "",
                                         "k1",
                                         "v2",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v1", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));
    }

    {
        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k3", "v3"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k3",
                                         pegasus_client::cas_check_type::CT_VALUE_NOT_EMPTY,
                                         "",
                                         "k4",
                                         "v4",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v3", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k4", value));
        ASSERT_EQ("v4", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k3"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));
    }
}
TEST_F(check_and_set, value_match_anywhere)
{
    std::string hash_key("check_and_set_test_value_match_anywhere");

    {
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_ANYWHERE,
                                         "v",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_FALSE(results.check_value_exist);
        ASSERT_EQ(PERR_NOT_FOUND, client_->get(hash_key, "k1", value));

        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k1", ""));

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_ANYWHERE,
                                         "v",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_ANYWHERE,
                                         "",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v1", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_ANYWHERE,
                                         "",
                                         "k1",
                                         "v2",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v1", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_ANYWHERE,
                                         "2",
                                         "k1",
                                         "v111v",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v111v", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_ANYWHERE,
                                         "111",
                                         "k1",
                                         "v2",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v111v", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_ANYWHERE,
                                         "y",
                                         "k1",
                                         "v3",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_ANYWHERE,
                                         "v2v",
                                         "k1",
                                         "v3",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_ANYWHERE,
                                         "v2",
                                         "k1",
                                         "v3",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v3", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));
    }

    {
        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k3", "v333v"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k3",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_ANYWHERE,
                                         "333",
                                         "k4",
                                         "v4",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v333v", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k4", value));
        ASSERT_EQ("v4", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k3"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));
    }
}

TEST_F(check_and_set, value_match_prefix)
{
    std::string hash_key("check_and_set_test_value_match_prefix");

    {
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_PREFIX,
                                         "v",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_FALSE(results.check_value_exist);
        ASSERT_EQ(PERR_NOT_FOUND, client_->get(hash_key, "k1", value));

        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k1", ""));

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_PREFIX,
                                         "v",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_PREFIX,
                                         "",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v1", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_PREFIX,
                                         "",
                                         "k1",
                                         "v2",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v1", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_PREFIX,
                                         "v",
                                         "k1",
                                         "v111v",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v111v", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_PREFIX,
                                         "111",
                                         "k1",
                                         "v2",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v111v", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v111v", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_PREFIX,
                                         "v111",
                                         "k1",
                                         "v2",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v111v", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_PREFIX,
                                         "y",
                                         "k1",
                                         "v3",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_PREFIX,
                                         "v2v",
                                         "k1",
                                         "v3",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_PREFIX,
                                         "2",
                                         "k1",
                                         "v3",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_PREFIX,
                                         "v2",
                                         "k1",
                                         "v3",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v3", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));
    }

    {
        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k3", "v333v"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k3",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_PREFIX,
                                         "v333",
                                         "k4",
                                         "v4",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v333v", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k4", value));
        ASSERT_EQ("v4", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k3"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));
    }
}

TEST_F(check_and_set, value_match_postfix)
{
    std::string hash_key("check_and_set_test_value_match_postfix");

    {
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_POSTFIX,
                                         "v",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_FALSE(results.check_value_exist);
        ASSERT_EQ(PERR_NOT_FOUND, client_->get(hash_key, "k1", value));

        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k1", ""));

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_POSTFIX,
                                         "v",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_POSTFIX,
                                         "",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v1", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_POSTFIX,
                                         "",
                                         "k1",
                                         "v2",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v1", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_POSTFIX,
                                         "2",
                                         "k1",
                                         "v111v",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v111v", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_POSTFIX,
                                         "111",
                                         "k1",
                                         "v2",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v111v", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v111v", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_POSTFIX,
                                         "111v",
                                         "k1",
                                         "v2",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v111v", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_POSTFIX,
                                         "y",
                                         "k1",
                                         "v3",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_POSTFIX,
                                         "2v2",
                                         "k1",
                                         "v3",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_POSTFIX,
                                         "v",
                                         "k1",
                                         "v3",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_POSTFIX,
                                         "v2",
                                         "k1",
                                         "v3",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v3", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));
    }

    {
        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k3", "v333v"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k3",
                                         pegasus_client::cas_check_type::CT_VALUE_MATCH_POSTFIX,
                                         "333v",
                                         "k4",
                                         "v4",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v333v", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k4", value));
        ASSERT_EQ("v4", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k3"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));
    }
}

TEST_F(check_and_set, value_bytes_compare)
{
    std::string hash_key("check_and_set_test_value_bytes_compare");

    {
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_BYTES_EQUAL,
                                         "",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_FALSE(results.check_value_exist);
        ASSERT_EQ(PERR_NOT_FOUND, client_->get(hash_key, "k1", value));

        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k1", ""));

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_BYTES_EQUAL,
                                         "",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v1", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_BYTES_EQUAL,
                                         "",
                                         "k1",
                                         "v2",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v1", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v1", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_BYTES_EQUAL,
                                         "v1",
                                         "k1",
                                         "v2",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v1", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("v2", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));
    }

    {
        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k3", "v3"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k3",
                                         pegasus_client::cas_check_type::CT_VALUE_BYTES_EQUAL,
                                         "v3",
                                         "k4",
                                         "v4",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v3", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k4", value));
        ASSERT_EQ("v4", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k3"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));
    }

    {
        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k5", "v1"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        // v1 < v2
        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k5",
                                         pegasus_client::cas_check_type::CT_VALUE_BYTES_LESS,
                                         "v2",
                                         "k5",
                                         "v2",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v1", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k5", value));
        ASSERT_EQ("v2", value);

        // v2 <= v2
        options.return_check_value = true;
        ASSERT_EQ(
            PERR_OK,
            client_->check_and_set(hash_key,
                                   "k5",
                                   pegasus_client::cas_check_type::CT_VALUE_BYTES_LESS_OR_EQUAL,
                                   "v2",
                                   "k5",
                                   "v3",
                                   options,
                                   results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k5", value));
        ASSERT_EQ("v3", value);

        // v3 <= v4
        options.return_check_value = true;
        ASSERT_EQ(
            PERR_OK,
            client_->check_and_set(hash_key,
                                   "k5",
                                   pegasus_client::cas_check_type::CT_VALUE_BYTES_LESS_OR_EQUAL,
                                   "v4",
                                   "k5",
                                   "v4",
                                   options,
                                   results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v3", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k5", value));
        ASSERT_EQ("v4", value);

        // v4 >= v4
        options.return_check_value = true;
        ASSERT_EQ(
            PERR_OK,
            client_->check_and_set(hash_key,
                                   "k5",
                                   pegasus_client::cas_check_type::CT_VALUE_BYTES_GREATER_OR_EQUAL,
                                   "v4",
                                   "k5",
                                   "v5",
                                   options,
                                   results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v4", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k5", value));
        ASSERT_EQ("v5", value);

        // v5 >= v4
        options.return_check_value = true;
        ASSERT_EQ(
            PERR_OK,
            client_->check_and_set(hash_key,
                                   "k5",
                                   pegasus_client::cas_check_type::CT_VALUE_BYTES_GREATER_OR_EQUAL,
                                   "v4",
                                   "k5",
                                   "v6",
                                   options,
                                   results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v5", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k5", value));
        ASSERT_EQ("v6", value);

        // v6 > v5
        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k5",
                                         pegasus_client::cas_check_type::CT_VALUE_BYTES_GREATER,
                                         "v5",
                                         "k5",
                                         "v7",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("v6", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k5", value));
        ASSERT_EQ("v7", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k5"));
    }
}

TEST_F(check_and_set, value_int_compare)
{
    std::string hash_key("check_and_set_test_value_int_compare");

    {
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_INT_EQUAL,
                                         "1",
                                         "k1",
                                         "2",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_FALSE(results.check_value_exist);
        ASSERT_EQ(PERR_NOT_FOUND, client_->get(hash_key, "k1", value));

        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k1", ""));

        options.return_check_value = true;
        ASSERT_EQ(PERR_INVALID_ARGUMENT,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_INT_EQUAL,
                                         "1",
                                         "k1",
                                         "2",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("", value);

        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k1", "1"));

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_INT_EQUAL,
                                         "1",
                                         "k1",
                                         "2",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("1", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_INVALID_ARGUMENT,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_INT_EQUAL,
                                         "",
                                         "k1",
                                         "3",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_INVALID_ARGUMENT,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_INT_EQUAL,
                                         "v1",
                                         "k1",
                                         "3",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("2", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_INVALID_ARGUMENT,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_INT_EQUAL,
                                         "88888888888888888888888888888888888888888888888",
                                         "k1",
                                         "3",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("2", value);

        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k1", "0"));

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_INT_EQUAL,
                                         "0",
                                         "k1",
                                         "-1",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("0", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("-1", value);

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         pegasus_client::cas_check_type::CT_VALUE_INT_EQUAL,
                                         "-1",
                                         "k1",
                                         "-2",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("-1", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k1", value));
        ASSERT_EQ("-2", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k1"));
    }

    {
        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k3", "3"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k3",
                                         pegasus_client::cas_check_type::CT_VALUE_INT_EQUAL,
                                         "3",
                                         "k4",
                                         "4",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("3", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k4", value));
        ASSERT_EQ("4", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k3"));
        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k4"));
    }

    {
        ASSERT_EQ(PERR_OK, client_->set(hash_key, "k5", "1"));

        std::string value;
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        // 1 < 2
        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k5",
                                         pegasus_client::cas_check_type::CT_VALUE_INT_LESS,
                                         "2",
                                         "k5",
                                         "2",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("1", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k5", value));
        ASSERT_EQ("2", value);

        // 2 <= 2
        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k5",
                                         pegasus_client::cas_check_type::CT_VALUE_INT_LESS_OR_EQUAL,
                                         "2",
                                         "k5",
                                         "3",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("2", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k5", value));
        ASSERT_EQ("3", value);

        // 3 <= 4
        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k5",
                                         pegasus_client::cas_check_type::CT_VALUE_INT_LESS_OR_EQUAL,
                                         "4",
                                         "k5",
                                         "4",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("3", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k5", value));
        ASSERT_EQ("4", value);

        // 4 >= 4
        options.return_check_value = true;
        ASSERT_EQ(
            PERR_OK,
            client_->check_and_set(hash_key,
                                   "k5",
                                   pegasus_client::cas_check_type::CT_VALUE_INT_GREATER_OR_EQUAL,
                                   "4",
                                   "k5",
                                   "5",
                                   options,
                                   results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("4", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k5", value));
        ASSERT_EQ("5", value);

        // 5 >= 4
        options.return_check_value = true;
        ASSERT_EQ(
            PERR_OK,
            client_->check_and_set(hash_key,
                                   "k5",
                                   pegasus_client::cas_check_type::CT_VALUE_INT_GREATER_OR_EQUAL,
                                   "4",
                                   "k5",
                                   "6",
                                   options,
                                   results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("5", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k5", value));
        ASSERT_EQ("6", value);

        // 6 > 5
        options.return_check_value = true;
        ASSERT_EQ(PERR_OK,
                  client_->check_and_set(hash_key,
                                         "k5",
                                         pegasus_client::cas_check_type::CT_VALUE_INT_GREATER,
                                         "5",
                                         "k5",
                                         "7",
                                         options,
                                         results));
        ASSERT_TRUE(results.set_succeed);
        ASSERT_TRUE(results.check_value_returned);
        ASSERT_TRUE(results.check_value_exist);
        ASSERT_EQ("6", results.check_value);
        ASSERT_EQ(PERR_OK, client_->get(hash_key, "k5", value));
        ASSERT_EQ("7", value);

        ASSERT_EQ(PERR_OK, client_->del(hash_key, "k5"));
    }
}

TEST_F(check_and_set, invalid_type)
{
    std::string hash_key("check_and_set_test_value_invalid_type");

    {
        pegasus_client::check_and_set_options options;
        pegasus_client::check_and_set_results results;

        options.return_check_value = true;
        ASSERT_EQ(PERR_INVALID_ARGUMENT,
                  client_->check_and_set(hash_key,
                                         "k1",
                                         (pegasus_client::cas_check_type)100,
                                         "v",
                                         "k1",
                                         "v1",
                                         options,
                                         results));
        ASSERT_FALSE(results.set_succeed);
        ASSERT_FALSE(results.check_value_returned);
    }
}
