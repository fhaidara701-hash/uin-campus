#pragma once
#include "uincampus/regles.hpp"
#include <span>

namespace uin {

/// Indicateurs statistiques d'une série de notes.
struct Statistiques {
    double minimum{};
    double maximum{};
    double moyenne{};
    double ecartType{};
};

/// Somme des valeurs.
[[nodiscard]] double somme(std::span<const double> valeurs);

/// Moyenne arithmétique.
/// @pre notes n'est pas vide
[[nodiscard]] double moyenne(std::span<const double> notes);

/// Moyenne pondérée par les coefficients.
/// @throws std::invalid_argument si les tailles diffèrent, notes est vide ou si
/// la somme des coefficients n'est pas positive.
/// @throws std::overflow_error si une somme n'est pas représentable.
[[nodiscard]] double moyenne(std::span<const double> notes,
                             std::span<const double> coefficients);

/// Minimum, maximum, moyenne et écart-type.
/// @throws std::invalid_argument si notes est vide ou contient une valeur non finie.
[[nodiscard]] Statistiques calculerStatistiques(std::span<const double> notes);

/// Nombre de notes supérieures ou égales au seuil.
/// @throws std::invalid_argument si le seuil n'est pas fini.
[[nodiscard]] std::size_t compterValidees(
    std::span<const double> notes, double seuil = seuilValidation);

/// Arrondi au nombre de décimales demandé.
/// @throws std::invalid_argument si la valeur n'est pas finie.
/// @throws std::out_of_range si le facteur d'arrondi n'est pas représentable.
[[nodiscard]] double arrondir(double valeur, int decimales = 2);

} // namespace uin
