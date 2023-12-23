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
                float day_rent_cost
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
            float get_day_rent_cost() const;
            void set_day_rent_cost(float day_rent_cost);
            void update(
                const std::string& make,
                const std::string& model,
                int year,
                int mileage,
                int min_rent,
                int max_rent,
                float day_rent_cost
            );

        private:
            int id_;
            std::string make_;
            std::string model_;
            int year_;
            int mileage_;
            int min_rent_;
            int max_rent_;
            float day_rent_cost_;
    };

}

#endif
