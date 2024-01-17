#ifndef CAR_LIST_FILTERS_H
#define CAR_LIST_FILTERS_H
#include "core/car/date_ymd.h"
#include <string>
#include <vector>

namespace crs::core::service
{
    class car_list_filters
    {
        public:
            static const std::string SORT_ID;
            static const std::string SORT_MODEL;
            static const std::string SORT_MAKE;
            static const std::string SORT_PRICE;
            static const std::string SORT_YEAR;
            static const std::string SORT_MIN_RENT;
            static const std::string SORT_MAX_RENT;

            static const std::string get_allowed_sort_fields_text();

            car_list_filters();

            void validate();
            const int get_days_amount() const;
            const bool has_period() const;

            car::date_ymd* get_start_ymd() const;
            void set_start_ymd(car::date_ymd* start_ymd);

            car::date_ymd* get_end_ymd() const;
            void set_end_ymd(car::date_ymd* end_ymd);

            void set_model(std::string model);
            const std::string get_model() const;

            void set_make(std::string make);
            const std::string get_make() const;

            void set_year_from(const int year_from);
            const int get_year_from() const;

            void set_year_to(const int year_to);
            const int get_year_to() const;

            void set_price_from(const float price_from);
            const float get_price_from() const;

            void set_price_to(const float price_to);
            const float get_price_to() const;

            void set_sort_field(const std::string sort_field);
            const std::string get_sort_field() const;

            void set_sort_order(const std::string sort_order);
            const std::string get_sort_order() const;

            const bool is_sort_asc() const;
        private:
            static const std::vector<std::string> ALLOWED_SORT_FIELDS;
            crs::core::car::date_ymd* start_ymd_;
            crs::core::car::date_ymd* end_ymd_;
            std::string model_;
            std::string make_;
            int year_from_;
            int year_to_;
            float price_from_;
            float price_to_;
            std::string sort_field_;
            std::string sort_order_;
    };

}

#endif
