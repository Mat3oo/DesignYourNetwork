#pragma once
#ifndef IPADDRESSBASE_H
#define IPADDRESSBASE_H

#include <boost/dynamic_bitset.hpp>
#include <memory>
#include <istream>

#include "IIPaddress.h"

namespace core {
    class IPmaskBase; //forward declaration

    class IPaddressBase : public virtual IIPaddress
    {
    public:
        IPaddressBase(const boost::dynamic_bitset<>& ipaddress): _IpAddress{ipaddress} {};

        friend std::shared_ptr<IPaddressBase> operator&(const IPaddressBase& ip, const IPmaskBase& mask);
        bool operator==(const IPaddressBase&) const;
        bool operator!=(const IPaddressBase&) const;

        friend std::istream& operator>>(std::istream&, std::shared_ptr<IPaddressBase>&);

        virtual ~IPaddressBase() = default;
    protected:
        virtual std::shared_ptr<IPaddressBase> _applyMask(const boost::dynamic_bitset<>& maskBitset) const = 0;

//        IPaddressBase& operator=(const IPaddressBase&) = default; //no neeed to prevent slicing, as long as derived class doesn't have more members

        boost::dynamic_bitset<> _IpAddress;
    };
};

#endif // IPADDRESSBASE_H
