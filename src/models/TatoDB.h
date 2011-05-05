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
 * @package  Models
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */


#ifndef TATOEBACPP_MODELS_TATODB_H
#define TATOEBACPP_MODELS_TATODB_H

#include <iostream>
#include "generics/Singleton.h"

extern "C" {
#include "tato/db.h"
}

#define GET_DB_POINTER() TatoDB::get_instance("")->get_db_pointer()

/**
 * @class TatoDB
 * singleton representing the graph database of tatoeba
 */
class TatoDB : public Singleton<TatoDB>{
    friend class Singleton<TatoDB>;

    private:
        /**
         * Pointer on the graph database structure
         */
        TatoDb *tatoDb;
        /**
         * Constructor, will create a tatodb graph database
         * and fill it with the data at data_path
         */
        TatoDB(std::string data_path);
        /**
         * destructor
         */
        ~TatoDB();

    public:
        /**
         * Will return the pointer on the tatodb graph structure
         */
        TatoDb *get_db_pointer();
        

};


#endif
