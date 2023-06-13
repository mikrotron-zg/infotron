/*
 * This file is part of Infotron project (https://github.com/mikrotron-zg/infotron)
 * developed by Mikrotron d.o.o. (http://mikrotron.hr).
 * It contains basic crypto info handler for CoinAPI.io (https://docs.coinapi.io/).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version. See the LICENSE file at the 
 * top-level directory of this distribution for details 
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CRYPTO_INFO_H
    #define CRYPTO_INFO_H
    #define CRYPTO_API_PREFIX "https://rest.coinapi.io/v1/exchangerate/"
    // Define cuurency for exchange rate
    #define EX_CURRENCY "USD"

    /**
     * @brief Gets crypto info from CoinAPI.io
     * 
     * Connects to server, downloads and parses received JSON file. There
     * is a daily limit for free account, make sure not to exceed the limit.
     */
    void getCryptoInfo();
#endif