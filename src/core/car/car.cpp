#include "car.h"
#include <core/core_exception.hpp>

namespace crs::core::car
{
    car::car()
    {
        id_ = 0;
        make_ = "";
        model_ = "";
        year_ = 0;
    }

    car::car(
        const string& make,
        const string& model,
        int year,
        int mileage,
        int minRent,
        int maxRent) : make_(make), model_(model),
                       year_(year), mileage_(mileage),
                       min_rent_(minRent), max_rent_(maxRent)
    {
        if (make_.empty() || model_.empty() || year_ <= 0)
        {
            throw crs::core::core_exception("Make, model and year are required fields.");
        }
    }

    void car::update(
        const string& make,
        const string& model,
        int year,
        int mileage,
        int min_rent,
        int max_rent)
    {
        if (!make.empty())
        {
            make_ = make;
        }
        if (!model.empty())
        {
            model_ = model;
        }
        if (year > 0)
        {
            year_ = year;
        }
        if (mileage > 0)
        {
            mileage_ = mileage;
        }

        if (max_rent > 0)
        {
            max_rent_ = max_rent;
        }

        if (min_rent > 0)
        {
            min_rent_ = min_rent;
        }
    }

    int car::get_id() const
    {
        return id_;
    }

    void car::set_id(int id)
    {
        id_ = id;
    }

    const string& car::get_make() const
    {
        return make_;
    }

    void car::set_make(const std::string& make)
    {
        make_ = make;
    }

    const string& car::get_model() const
    {
        return model_;
    }

    void car::set_model(const string& model)
    {
        model_ = model;
    }

    int car::get_year() const
    {
        return year_;
    }

    void car::set_year(int year)
    {
        year_ = year;
    }

    int car::get_mileage() const
    {
        return mileage_;
    }

    void car::set_mileage(int mileage)
    {
        mileage_ = mileage;
    }

    int car::get_min_rent() const
    {
        return min_rent_;
    }

    void car::set_min_rent(int minRent)
    {
        min_rent_ = minRent;
    }

    int car::get_max_rent() const
    {
        return max_rent_;
    }

    void car::set_max_rent(int maxRent)
    {
        max_rent_ = maxRent;
    }

}