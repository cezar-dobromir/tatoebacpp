/**
 * Tatoeba Project, free collaborative creation of multilingual corpuses project
 * Copyright (C) 2011 Allan SIMON <allan.simon@supinfo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * @category Tatoebacpp
 * @package  Singletons
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */



#ifndef SHDICT_GENERICS_LANGUAGES_H
#define SHDICT_GENERICS_LANGUAGES_H

#include <map>
#include "Singleton.h"
#include <cppcms/json.h>

typedef std::map<std::string, std::string> ISOToNameMap;
typedef std::map<int, std::string> IdToISOMap;
typedef std::map<std::string, int> ISOToIdMap;


/**
 * Singleton class used to store the information about the
 * languages supported in Tatoeba, and their related info
 * ISO code, name, id in the database 
 */
class Languages : public Singleton<Languages> {
    friend class Singleton<Languages>;

    private:
        /**
         * Map associating ISO code to the English name
         **/
        ISOToNameMap isoToName;

        /**
         * Map associating internal ID in the database to ISO code
         */
        IdToISOMap idToISO;

        /**
         * Map associating the ISO code to internal ID
         */
        ISOToIdMap isoToId;
        Languages();

    public:
        /**
         * return the map ISO code => English name
         */
        ISOToNameMap get_iso_to_name_map();
        
        /**
         * Initialize the singleton with the data stored in config.js 
         */
        void init(cppcms::json::object langsJson);

        /**
         * Return the internal id associated to the ISO code of a given language
         */
        int get_id_from_iso(std::string isoCode);

        /**
         * Return the ISO code associated to the internal ID of a given language
         */
        std::string get_iso_from_id(int id);

};

#endif