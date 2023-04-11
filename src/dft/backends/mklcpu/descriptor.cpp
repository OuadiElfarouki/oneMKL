/*******************************************************************************
* Copyright 2023 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions
* and limitations under the License.
*
*
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#include "oneapi/mkl/dft/descriptor.hpp"
#include "../../descriptor.cxx"

#include "oneapi/mkl/dft/detail/mklcpu/onemkl_dft_mklcpu.hpp"

namespace oneapi {
namespace mkl {
namespace dft {

template <precision prec, domain dom>
void descriptor<prec, dom>::commit(backend_selector<backend::mklcpu> selector) {
    if (!pimpl_ || pimpl_->get_queue() != selector.get_queue()) {
        if (pimpl_) {
            pimpl_->get_queue().wait();
        }
        pimpl_.reset(mklcpu::create_commit(*this, selector.get_queue()));
    }
    pimpl_->commit(values_);
}

template void descriptor<precision::SINGLE, domain::COMPLEX>::commit(
    backend_selector<backend::mklcpu>);
template void descriptor<precision::SINGLE, domain::REAL>::commit(
    backend_selector<backend::mklcpu>);
template void descriptor<precision::DOUBLE, domain::COMPLEX>::commit(
    backend_selector<backend::mklcpu>);
template void descriptor<precision::DOUBLE, domain::REAL>::commit(
    backend_selector<backend::mklcpu>);

} //namespace dft
} //namespace mkl
} //namespace oneapi
