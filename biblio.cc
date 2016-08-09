#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
// Chaines de caractères à utiliser pour les affichages:
/*

  été jeté

  d'un

  n'est

  L'oeuvre

  bibliothèque

  détruit

*/

class Auteur {
private:
  const string nom;
  bool prime;

public:
  Auteur(const string nom, bool prime=false) : nom(nom), prime(prime) {

  }

  Auteur(Auteur const &copy) = delete;

  string getNom() const {return nom;}
  bool getPrix() const {return prime;}
};

class Oeuvre {
private:
  const string titre;
  const Auteur& auteur;
  const string langue;
public:
  Oeuvre(const string titre,const  Auteur &auteur, const string langue) : titre(titre), auteur(auteur), langue(langue) {}
  ~Oeuvre() {
    cout << "L’oeuvre \""<<titre<<", "<<auteur.getNom()<<", en "<<langue<<"\" n’est plus disponible." << endl;
  }

  const Auteur& getAuteur() const {return auteur;}
  string getLangue() const {return langue;}
  string getTitre() const {return titre;}

  void afficher() {
    cout << titre<<", "<<auteur.getNom()<<", en "<< langue << endl;
  }
};

class Exemplaire {
private:
  const Oeuvre& oeuvre;
public:
  Exemplaire(Oeuvre const &oeuvre) : oeuvre(oeuvre) {
    cout << "Nouvel exemplaire de : "<<oeuvre.getTitre()<<", "<<oeuvre.getAuteur().getNom()<<", en "<< oeuvre.getLangue()<< endl;
  }
  Exemplaire(Exemplaire const &ex) : oeuvre(ex.getOeuvre()) {
    //this->oeuvre = Oeuvre(ex.getOeuvre());
    cout << "Copie d'un exemplaire de : "<<oeuvre.getTitre()<<", "<<oeuvre.getAuteur().getNom()<<", en "<< oeuvre.getLangue()<< endl;
  }
  ~Exemplaire() {
    cout << "Un exemplaire de \""<<oeuvre.getTitre()<<", "<<oeuvre.getAuteur().getNom()<<", en "<<oeuvre.getLangue() << "\" a été jeté !" <<endl;
  }

  const Oeuvre& getOeuvre() const {return oeuvre;}

  void affiche() const {
    cout << "Exemplaire de : "<<oeuvre.getTitre()<<", "<<oeuvre.getAuteur().getNom()<<", en "<<oeuvre.getLangue() << endl;
  }

};

class Bibliotheque {
private:
  const string nom;
  vector<Exemplaire> liste;
public:
  Bibliotheque(const string nom) : nom(nom) {
    cout << "La bibliothèque "<< nom<<" est ouverte !" << endl;

  }
  ~Bibliotheque() {
    cout << "La bibliothèque "<<nom<<" ferme ses portes, et détruit ses exemplaires :" << endl;
  }

  string getNom() const {return nom;}

  void stocker(Oeuvre& o, int nombre=1) {
    for (int i=0; i<nombre; i++) {
      //Exemplaire ex(o);
      liste.push_back(Exemplaire(o));//ex);
    }
  }

  void lister_exemplaires(string langue="") const {

    for (auto const & ex : liste) {
      if (langue == "" || langue == ex.getOeuvre().getLangue()) {
        ex.affiche();
      }
    }

    /* for_each(liste.begin(), liste.end(), [langue](const Exemplaire& ex){
       if (langue == "" || langue == ex.getOeuvre().getLangue()) {
       ex.affiche();
       }
       });*/

  }

  int compter_exemplaires(Oeuvre& o) const {
    int x=0;

    for (auto const & ex : liste) {
      auto exo = ex.getOeuvre();
      if (o.getAuteur().getNom() == exo.getAuteur().getNom() && o.getTitre() ==  exo.getTitre() ) {
        x++;
      }

    }

/*    for_each(liste.begin(), liste.end(), [o,&x](const Exemplaire& ex){
        auto exo = ex.getOeuvre();
        if (o.getAuteur().getNom() == exo.getAuteur().getNom() && o.getTitre() ==  exo.getTitre() ) {
          x++;
        }
        });*/
    return x;
  }

  void afficher_auteurs(bool prix=false) {
    for_each(liste.begin(), liste.end(), [prix](const Exemplaire& ex){
        auto a = ex.getOeuvre().getAuteur().getPrix();
        if (!prix || a ) {
          cout << ex.getOeuvre().getAuteur().getNom() << endl;
        }
      });

  }
};

/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{

  Auteur a1("Victor Hugo"),
    a2("Alexandre Dumas"),
    a3("Raymond Queneau", true);

  Oeuvre o1("Les Misérables"           , a1, "français" ),
    o2("L'Homme qui rit"          , a1, "français" ),
    o3("Le Comte de Monte-Cristo" , a2, "français" ),
    o4("Zazie dans le métro"      , a3, "français" ),
    o5("The Count of Monte-Cristo", a2, "anglais" );

  Bibliotheque biblio("municipale");
  biblio.stocker(o1, 2);
  biblio.stocker(o2);
  biblio.stocker(o3, 3);
  biblio.stocker(o4);
  biblio.stocker(o5);

  cout << "La bibliothèque " << biblio.getNom()
       << " offre les exemplaires suivants :" << endl;
  biblio.lister_exemplaires();

  const string langue("anglais");
  cout << " Les exemplaires en "<< langue << " sont :" << endl;
  biblio.lister_exemplaires(langue);

  cout << " Les auteurs à succès sont :" << endl;
  biblio.afficher_auteurs(true);

  cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       << o3.getTitre() << endl;

  return 0;
}
