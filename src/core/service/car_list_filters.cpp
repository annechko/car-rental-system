#include "car_list_filters.h"
#include "core/core_exception.hpp"
#include <numeric>
#include <set>

namespace crs::core::service
{
    const std::string car_list_filters::SORT_ID = "id";

    const std::string car_list_filters::SORT_MODEL = "model";

    const std::string car_list_filters::SORT_MAKE = "make";

    const std::string car_list_filters::SORT_PRICE = "price";

    const std::string car_list_filters::SORT_YEAR = "year";

    const std::string car_list_filters::SORT_MIN_RENT = "min-rent";

    const std::string car_list_filters::SORT_MAX_RENT = "max-rent";

    const std::vector<std::string> car_list_filters::ALLOWED_SORT_FIELDS =
        std::vector<std::string>{
            car_list_filters::SORT_MAKE,
            car_list_filters::SORT_MODEL,
            car_list_filters::SORT_YEAR,
            car_list_filters::SORT_PRICE,
            car_list_filters::SORT_MIN_RENT,
            car_list_filters::SORT_MAX_RENT,
        };

    car_list_filters::car_list_filters()
    {
        start_ymd_ = nullptr;
        end_ymd_ = nullptr;
        model_ = "";
        make_ = "";
        sort_field_ = "";
        sort_order_ = "";
        year_from_ = 0;
        year_to_ = 0;
        price_from_ = 0.0;
        price_to_ = 0.0;
    }

    void car_list_filters::validate()
    {
        if ((start_ymd_ != nullptr && end_ymd_ == nullptr)
            || (start_ymd_ == nullptr && end_ymd_ != nullptr))
        {
            throw core::core_exception("Both start and end are required to specify a period.");
        }
        if (year_from_ > 0)
        {
            if (year_from_ > 2050 || year_from_ < 1600)
            {
                throw core::core_exception("Year should be between 1600 and 2050.");
            }
        }
        if (year_to_ > 0)
        {
            if (year_to_ > 2050 || year_to_ < 1600)
            {
                throw core::core_exception("Year should be between 1600 and 2050.");
            }
        }
        if (sort_order_ != "" && sort_field_ == "")
        {
            throw core::core_exception("Sort field is required when sort order specified.");
        }
        if (sort_order_ != "")
        {
            if (std::set < std::string > {"asc", "desc"}.count(sort_order_) == 0)
            {
                throw core::core_exception("Sort order must be one of [asc|desc].");
            }
        }
        if (sort_field_ != "")
        {
            if (std::count(ALLOWED_SORT_FIELDS.begin(), ALLOWED_SORT_FIELDS.end(), sort_field_) == 0)
            {
                throw core::core_exception(
                    "Sort field must be one of [" + car_list_filters::get_allowed_sort_fields_text() + "].");
            }
        }
    }

    const int car_list_filters::get_days_amount() const
    {
        if (start_ymd_ == nullptr || end_ymd_ == nullptr)
        {
            return -1;
        }

        return get_start_ymd()->count_days_till(get_end_ymd());
    }

    const bool car_list_filters::has_period() const
    {
        return start_ymd_ != nullptr && end_ymd_ != nullptr;
    }

    const std::string car_list_filters::get_allowed_sort_fields_text()
    {
        return std::accumulate(
            std::next(ALLOWED_SORT_FIELDS.begin()),
            ALLOWED_SORT_FIELDS.end(),
            ALLOWED_SORT_FIELDS[0],
            [](std::string a, std::string b) {
                return a + '|' + b;
            }
        );
    }

    const bool car_list_filters::is_sort_asc() const
    {
        return get_sort_order() != "desc";
    }

    car::date_ymd* car_list_filters::get_start_ymd() const
    {
        return start_ymd_;
    }

    void car_list_filters::set_start_ymd(car::date_ymd* start_ymd)
    {
        start_ymd_ = start_ymd;
    }

    car::date_ymd* car_list_filters::get_end_ymd() const
    {
        return end_ymd_;
    }

    void car_list_filters::set_end_ymd(car::date_ymd* end_ymd)
    {
        end_ymd_ = end_ymd;
    }

    void car_list_filters::set_model(std::string model)
    {
        model_ = model;
    }

    const std::string car_list_filters::get_model() const
    {
        return model_;
    }

    void car_list_filters::set_make(std::string make)
    {
        make_ = make;
    }

    const std::string car_list_filters::get_make() const
    {
        return make_;
    }

    void car_list_filters::set_year_from(const int year_from)
    {
        year_from_ = year_from;
    }

    const int car_list_filters::get_year_from() const
    {
        return year_from_;
    }

    void car_list_filters::set_year_to(const int year_to)
    {
        year_to_ = year_to;
    }

    const int car_list_filters::get_year_to() const
    {
        return year_to_;
    }

    void car_list_filters::set_price_from(const float price_from)
    {
        price_from_ = price_from;
    }

    const float car_list_filters::get_price_from() const
    {
        return price_from_;
    }

    void car_list_filters::set_price_to(const float price_to)
    {
        price_to_ = price_to;
    }

    const float car_list_filters::get_price_to() const
    {
        return price_to_;
    }

    void car_list_filters::set_sort_field(const std::string sort_field)
    {
        sort_field_ = sort_field;
    }

    const std::string car_list_filters::get_sort_field() const
    {
        return sort_field_;
    }

    void car_list_filters::set_sort_order(const std::string sort_order)
    {
        sort_order_ = sort_order;
    }

    const std::string car_list_filters::get_sort_order() const
    {
        return sort_order_;
    }
}
