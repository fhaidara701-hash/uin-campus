#include "uincampus/regles.hpp"

namespace uin {

Mention mentionPour(double moyenne) {
    if (moyenne >= seuilsMentions[3]) {
        return Mention::TresBien;
    }
    if (moyenne >= seuilsMentions[2]) {
        return Mention::Bien;
    }
    if (moyenne >= seuilsMentions[1]) {
        return Mention::AssezBien;
    }
    if (moyenne >= seuilsMentions[0]) {
        return Mention::Passable;
    }
    return Mention::Ajourne;
}

std::string_view libelle(Mention mention) {
    switch (mention) {
        case Mention::Ajourne:
            return "Ajourné";
        case Mention::Passable:
            return "Passable";
        case Mention::AssezBien:
            return "Assez bien";
        case Mention::Bien:
            return "Bien";
        case Mention::TresBien:
            return "Très bien";
    }
    return "Inconnu";
}

} // namespace uin
