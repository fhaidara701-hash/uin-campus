#include "uincampus/calculs.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <stdexcept>

namespace uin {
namespace {

void verifierNonVide(std::span<const double> valeurs, const char* fonction) {
    if (valeurs.empty()) {
        throw std::invalid_argument(fonction);
    }
}

void verifierValeurFinie(double valeur, const char* fonction) {
    if (!std::isfinite(valeur)) {
        throw std::invalid_argument(fonction);
    }
}

void verifierValeursFinies(std::span<const double> valeurs, const char* fonction) {
    for (double valeur : valeurs) {
        verifierValeurFinie(valeur, fonction);
    }
}

} // namespace

double somme(std::span<const double> valeurs) {
    verifierValeursFinies(valeurs, "somme(): valeur non finie");
    const double resultat = std::accumulate(valeurs.begin(), valeurs.end(), 0.0);
    if (!std::isfinite(resultat)) {
        throw std::overflow_error("somme(): résultat non fini");
    }
    return resultat;
}

double moyenne(std::span<const double> notes) {
    verifierNonVide(notes, "moyenne(): aucune note");
    return somme(notes) / static_cast<double>(notes.size());
}

double moyenne(std::span<const double> notes,
               std::span<const double> coefficients) {
    verifierNonVide(notes, "moyenne(): aucune note");
    if (notes.size() != coefficients.size()) {
        throw std::invalid_argument("moyenne(): tailles différentes");
    }
    const double sommeCoefficients = somme(coefficients);
    if (sommeCoefficients <= 0.0) {
        throw std::invalid_argument("moyenne(): somme des coefficients non positive");
    }
    const double sommePonderee =
        std::inner_product(notes.begin(), notes.end(), coefficients.begin(), 0.0);
    if (!std::isfinite(sommePonderee)) {
        throw std::overflow_error("moyenne(): somme pondérée non finie");
    }
    const double resultat = sommePonderee / sommeCoefficients;
    if (!std::isfinite(resultat)) {
        throw std::overflow_error("moyenne(): résultat non fini");
    }
    return resultat;
}

Statistiques calculerStatistiques(std::span<const double> notes) {
    verifierNonVide(notes, "calculerStatistiques(): aucune note");
    const double moy = moyenne(notes);
    const auto [mini, maxi] = std::ranges::minmax(notes);
    const double sommeCarres = std::accumulate(
        notes.begin(), notes.end(), 0.0,
        [moy](double total, double n) { return total + (n - moy) * (n - moy); });
    const double ecartType =
        std::sqrt(sommeCarres / static_cast<double>(notes.size()));
    if (!std::isfinite(ecartType)) {
        throw std::overflow_error("calculerStatistiques(): écart-type non fini");
    }
    return Statistiques{
        .minimum = mini,
        .maximum = maxi,
        .moyenne = moy,
        .ecartType = ecartType,
    };
}

std::size_t compterValidees(std::span<const double> notes, double seuil) {
    verifierValeurFinie(seuil, "compterValidees(): seuil non fini");
    verifierValeursFinies(notes, "compterValidees(): note non finie");
    return static_cast<std::size_t>(
        std::ranges::count_if(notes, [seuil](double n) { return n >= seuil; }));
}

double arrondir(double valeur, int decimales) {
    verifierValeurFinie(valeur, "arrondir(): valeur non finie");
    const double facteur = std::pow(10.0, decimales);
    if (!std::isfinite(facteur) || facteur == 0.0) {
        throw std::out_of_range("arrondir(): nombre de décimales hors limites");
    }
    const double valeurMiseAEchelle = valeur * facteur;
    if (!std::isfinite(valeurMiseAEchelle)) {
        throw std::overflow_error("arrondir(): mise à l'échelle non finie");
    }
    const double resultat = std::round(valeurMiseAEchelle) / facteur;
    if (!std::isfinite(resultat)) {
        throw std::overflow_error("arrondir(): résultat non fini");
    }
    return resultat;
}

} // namespace uin
