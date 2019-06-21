//
// Created by qlu on 2019/1/21.
//

#ifndef PROJECT_BASIC_INFO_H
#define PROJECT_BASIC_INFO_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include <kungfu/wingchun/config.h>
#include <kungfu/wingchun/msg.h>

namespace kungfu
{
    namespace wingchun
    {
        class FutureInstrumentStorage
        {
        public:
            FutureInstrumentStorage(const std::string &file_name);

            void create_table_if_not_exist();

            void set_future_instruments(const std::vector<msg::data::FutureInstrument> &future_instruments);

            void get_future_instrument(std::pair<std::string, std::string> &key,
                                       std::map<std::pair<std::string, std::string>, msg::data::FutureInstrument> &future_instruments);

            void get_future_instruments(std::map<std::pair<std::string, std::string>, msg::data::FutureInstrument> &future_instruments);

        private:
            SQLite::Database db_;
        };

        class InstrumentManager
        {
        public:
            void reload_from_db();

            static std::shared_ptr<InstrumentManager> get_instrument_manager();

            const msg::data::FutureInstrument *get_future_instrument(const char *instrument_id, const char *exchange_id);

            int get_future_multiplier(const char *instrument_id, const char *exchange_id);

            double get_future_margin_ratio(const char *instrument_id, const char *exchange_id, Direction dir);

            std::vector<const msg::data::FutureInstrument *> get_future_instruments();

        private:
            InstrumentManager();

            static std::shared_ptr<InstrumentManager> instrument_manager_;
            std::map<std::pair<std::string, std::string>, msg::data::FutureInstrument> future_instruments_;
            msg::data::FutureInstrument default_future_instrument_;
        };
    }
} // namespace kungfu

#endif // PROJECT_BASIC_INFO_H
