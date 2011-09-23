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


#include "Tags.h"
#include "contents/tags.h"

namespace controllers {
namespace webs {
/**
 *
 */
Tags::Tags(cppcms::service &serv) : Controller(serv) {

    tagsModel = new models::Tags();

    cppcms::url_dispatcher* d = &dispatcher();
    d->assign("/view-all$", &Tags::view_all, this);
    d->assign("/sentences-with-tag/(.*)$", &Tags::sentences_with_tag, this, 1);
}

/**
 *
 */
Tags::~Tags() {
    delete tagsModel;
}

/**
 *
 */
void Tags::view_all() {

    contents::tags::ViewAll c;
    init_content(c);
    c.tagsList = tagsModel->get_all();

    render("tags_view_all", c);
}

/**
 *
 */
void Tags::sentences_with_tag(std::string tagName) {


    unsigned int page = get_page();

    contents::tags::SentencesWithTag c;
    init_content(c);
    c.filterLang.set_langs();
    c.tag = tagsModel->get(tagName);

    c.shc.sentences = tagsModel->sentences_with_tag(
        tagName,
        page
    );

    render("tags_sentences_with_tag", c);

}


} // End namespace webs 
} // End namespace controllers

