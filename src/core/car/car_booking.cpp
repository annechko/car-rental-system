#include "car_booking.h"

namespace crs::core::car
{
    const int car_booking::STATUS_NEW = 0;

    const int car_booking::STATUS_APPROVED = 1;

    car_booking::car_booking(
        int customer_id,
        int car_id,
        float price,
        int timestamp_start,
        int timestamp_end
    ) : customer_id_(customer_id), car_id_(car_id), price_(price),
        timestamp_start_(timestamp_start), timestamp_end_(timestamp_end)
    {
        init();
    }

    car_booking::car_booking()
    {
        init();
    }

    void car_booking::init()
    {
        status_ = car_booking::STATUS_NEW;
    }

    const int car_booking::get_id() const
    {
        return id_;
    }

    void car_booking::set_id(int id)
    {
        id_ = id;
    }

    int car_booking::get_customer_id() const
    {
        return customer_id_;
    }

    void car_booking::set_customer_id(int customer_id)
    {
        customer_id_ = customer_id;
    }

    int car_booking::get_car_id() const
    {
        return car_id_;
    }

    void car_booking::set_car_id(int car_id)
    {
        car_id_ = car_id;
    }

    float car_booking::get_price() const
    {
        return price_;
    }

    void car_booking::set_price(float price)
    {
        price_ = price;
    }

    int car_booking::get_timestamp_start() const
    {
        return timestamp_start_;
    }

    void car_booking::set_timestamp_start(int timestamp_start)
    {
        timestamp_start_ = timestamp_start;
    }

    int car_booking::get_timestamp_end() const
    {
        return timestamp_end_;
    }

    void car_booking::set_timestamp_end(int timestamp_end)
    {
        timestamp_end_ = timestamp_end;
    }

    int car_booking::get_status() const
    {
        return status_;
    }

    void car_booking::set_status(int status)
    {
        status_ = status;
    }

    const std::string car_booking::get_status_string() const
    {
        if (is_new())
        {
            return "NEW";
        }
        else if (is_approved())
        {
            return "APPROVED";
        }
        return "";
    }

    const bool car_booking::is_new() const
    {
        return status_ == STATUS_NEW;
    }

    const bool car_booking::is_approved() const
    {
        return status_ == STATUS_APPROVED;
    }
}

