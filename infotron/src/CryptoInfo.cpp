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

#include <Arduino_JSON.h>
#include "Configuration.h"
#include "CryptoInfo.h"
#include "WebServer.h"

double parseCryptoInfo(String input) {
    // Parse received JSON file
    JSONVar root = JSON.parse(input);
    if (JSON.typeof(root) == "undefined") {
        DEBUGLN("Parsing input failed!");
        return -99.9;
    }
    JSONVar keys = root.keys(); 
    return (double)(root[keys[3]]); // we need current rate only
}

void updateCryptoInfo(int i, double currentRate) {
  DEBUG("Current rate: "); DEBUGLN(currentRate);
  if (currentRate > 0) {
    cryptoInfo[i].lastValue = cryptoInfo[i].value;
    cryptoInfo[i].value = currentRate;
    if (cryptoInfo[i].lastValue > 0) {
      // Calculate change if we have last value
      cryptoInfo[i].change = (cryptoInfo[i].value - cryptoInfo[i].lastValue)/cryptoInfo[i].lastValue;
      DEBUG("Change: "); DEBUGLN(cryptoInfo[i].change);
    }
  }
}

void getCryptoInfo() {
  // Send API call to crypto info provider
  
  for (int i = 0; i < CRYPTO_NUM; i++) {
    String url = CRYPTO_API_PREFIX;
    DEBUG("Sending request for "); DEBUGLN(cryptoInfo[i].ticker);
    url += String(cryptoInfo[i].ticker) + "/" + EX_CURRENCY + "?apikey=" + String(CRYPTO_API_KEY);
    DEBUGLN(url);
    updateCryptoInfo(i, parseCryptoInfo(getApiResponse(url)));
  }
}