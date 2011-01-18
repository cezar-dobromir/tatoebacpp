#ifndef MODELS_SENTENCES_H
#define MODELS_SENTENCES_H

#include "models/TatoDB.h"

extern "C" {
#include "tato/fetcher_tree.h"
}

namespace models {

class Sentences {
    public:
        Sentences();
        TatoFetcherTree* getSentenceWithId(int id);
        int getRandomSentenceId();
};

}

#endif
