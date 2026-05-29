#pragma once

#include <algorithm>


//  STRATEGIJA 1 


//memory usage gali tapti milžiniškas kai darom su 10mil failu todel nera labai geras

template<typename Container>  //funkcija veikia su bet kokiu containeriu
void Strategija1(
    const Container& visi,
    Container& vargsiukai,
    Container& kietiakai
)
{
    vargsiukai.clear();
    kietiakai.clear();

    for (const auto& s : visi)
    {
        if (s.rez_vid < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakai.push_back(s);
    }
}

//  STRATEGIJA 2 

//nekeičia vargšiukų kopijos, O ištrina juos iš visi

//mažiau memory uzima lieka tik kietiakai originale

template<typename Container>
void Strategija2(
    Container& visi,
    Container& vargsiukai
)
{
    vargsiukai.clear();

    for (auto it = visi.begin(); it != visi.end(); )
    {
        if (it->rez_vid < 5.0)
        {
            vargsiukai.push_back(*it);
            it = visi.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
//  STRATEGIJA 3 

// tiesiog geriausiai veikia


template<typename Container>
void Strategija3(
    Container& visi,
    Container& vargsiukai
)
{
    auto border = std::stable_partition(
        visi.begin(),
        visi.end(),
        [](const Student& s)
        {
            return s.rez_vid >= 5.0;
        }
    );

    vargsiukai.insert(
        vargsiukai.end(),
        border,
        visi.end()
    );

    visi.erase(border, visi.end());
}
