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
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */

#include <cppcms/session_interface.h>
#include "Controller.h"
#include "Pages.h"

#include "contents/pages.h"
#include "models/Sentences.h"
#include "models/TatoDB.h"

#include "contents/forms/change_interface_langs.h"



namespace controllers {
namespace webs {

Pages::Pages(cppcms::service& serv) : controllers::webs::Controller(serv) {
    dispatcher().assign("", &Pages::homepage, this);
  	dispatcher().assign("/contribute", &Pages::contribute, this);
  	dispatcher().assign("/terms-of-use", &Pages::terms_of_use, this);
  	dispatcher().assign("change-interface-lang_treat", &Pages::change_interface_lang_treat, this);
  	dispatcher().assign("/tatoeba-team-and-credits", &Pages::team_and_credits, this);
}

/**
 *
 */
void Pages::change_interface_lang_treat() {
    forms::InterfaceLang form;
    form.set_langs();
    form.load(context());
    if(!form.validate()) {
        go_back_to_previous_page();
    }

    session()["interfaceLang"] =  form.interfaceLang.selected_id();

    go_back_to_previous_page();



}

/**
 *
 */
void Pages::homepage() {
    contents::pages::Homepage c;
    init_content(c);

    c.anotherRandomInLang.set_langs(
        get_current_user_spoken_langs()
    );

    c.totalNbrSentences = TatoDB::get_instance("")->get_total_nbr_sentences();
    c.sentencesStats = TatoDB::get_instance("")->get_top_five();

    models::Sentences sentencesModel;
	contents::helpers::Sentences shc(
        sentencesModel.get_random(
            get_depth(),
            get_current_user_spoken_langs()
        )
    );
    shc.currentUserHelper = c.usersHelper;
    c.shc = shc;
    render("homepage", c);
}

/**
 *
 */
void Pages::contribute() {
    contents::pages::Contribute c;
    init_content(c);
    render("contribute", c);
}


/**
 *
 */
void Pages::terms_of_use() {
    contents::pages::TermsOfUse c;
    init_content(c);
    render("termsofuse", c);
}


/**
 *
 */
void Pages::team_and_credits() {
    contents::pages::TeamAndCredits c;
    init_content(c);
    render("teamandcredits", c);
}

} // End namespace webs
} // End namespace controllers
