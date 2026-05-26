#ifndef SPLIT_H
#define SPLIT_H

#include "student.h"


template<typename Container>
void Strategija1(
    const Container& visi,
    Container& vargsiukai,
    Container& kietiakai
);


template<typename Container>
void Strategija2(
    Container& visi,
    Container& vargsiukai
);


template<typename Container>
void Strategija3(
    Container& visi,
    Container& vargsiukai
);

#include "split.tpp"

#endif