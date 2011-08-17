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

#include "OfUser.h"
#include "generics/Languages.h"
#include "models/Sentences.h"

namespace models {

/**
 *
 */
OfUser::OfUser(cppdb::session sqliteDb):
    SqliteModel(sqliteDb)
{

    sentencesModel = new models::Sentences();

}


/**
 *
 */
OfUser::~OfUser() {
    delete sentencesModel;
}


/**
 *
 */
/*
bool OfUser::adopt(
    const int sentenceId,
    const int userId,
    const std::string &isoCode
) {

    

}
*/

/**
 *
 */
bool OfUser::adopt_sentence(
    const int sentenceId,
    const int userId
) {
    std::string sentenceLang;
    if (!sentencesModel->get_lang(sentenceId,sentenceLang)) {
        return false;
    }


    cppdb::statement adopt = sqliteDb.prepare(
        "INSERT INTO sentence_users(sentence_id, user_id, lang_id) "
        "VALUES(?,?,?)"
    );
    adopt.bind(sentenceId);
    adopt.bind(userId);
    adopt.bind(
        Languages::get_instance()->get_id_from_iso(sentenceLang)
    );

    try {

        adopt.exec();        

    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
        adopt.reset();
        return false;
    }

    int affected = adopt.affected();
    adopt.reset();
    return affected == 1;

}


/**
 *
 */
bool OfUser::abandon_sentence(
    const int sentenceId,
    const int userId
) {


    return false;
}




}// end namespace models