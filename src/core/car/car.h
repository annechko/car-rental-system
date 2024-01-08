#ifndef _CAR_H_
#define _CAR_H_

#include <string>

namespace crs::core::car
{
    const int MAX_NAME_LENGTH = 30;

    class car
    {
        public:
            car();
            car(
                const std::string& make,
                const std::string& model,
                int year,
                int mileage,
                int min_rent,
                int max_rent,
                float price_per_day
            );
            int get_id() const;
            void set_id(int id);
            const std::string& get_make() const;
            void set_make(const std::string& make);
            const std::string& get_model() const;
            void set_model(const std::string& model);
            int get_year() const;
            void set_year(int year);
            int get_mileage() const;
            void set_mileage(int mileage);
            int get_min_rent() const;
            void set_min_rent(int min_rent);
            int get_max_rent() const;
            void set_max_rent(int max_rent);
            float get_price_per_day() const;
            void set_price_per_day(float price_per_day);
            void update(
                const std::string& make,
                const std::string& model,
                int year,
                int mileage,
                int min_rent,
                int max_rent,
                float price_per_day
            );

            const bool can_be_rented_for_days(int days) const;
        private:
            int id_;
            std::string make_;
            std::string model_;
            int year_;
            int mileage_;
            int min_rent_;
            int max_rent_;
            float price_per_day_;
    };

}

#endif
