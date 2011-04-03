/**
 * blitz::TinyVector serialization
 */

// SHARPEN is copyright (c) 2008  Ilya Loksha (primary author), Christopher Snow (project lead).
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files 
// (the "Software") to deal in the Software without restriction, including without limitation the rights to use, copy, modify, 
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions: 
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. 
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY 
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
// THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
// 



#include <boost/serialization/base_object.hpp>
#include <boost/serialization/binary_object.hpp>


#include <blitz/array.h>
#include <blitz/tinyvec-et.h>


namespace boost { namespace serialization { 

template <class Archive, class DataType, int N>
void serialize(Archive& ar, blitz::TinyVector<DataType, N>& v, const unsigned int version)
	{
        boost::serialization::binary_object binObj(
                 v.data(), sizeof(DataType) * N);
         ar & boost::serialization::make_nvp("TinyVector", binObj);
	}

}};