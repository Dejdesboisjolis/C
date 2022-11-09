
typedef struct Element Element;
typedef struct Liste Liste;

struct Element
{
    
int nombre;
Element *suivant;

};


struct Liste
{
    Element *premier;
};

void Pyramide(void);
Liste *init(void);
void insertion (Liste *liste, int nouveauNombre);
void suppression (Liste *liste);
void afficher(Liste *liste);
void ajout_milieu(Liste *liste, int nouveauNombre, int position);
void *myThreadFun(void *vargp);
void NProc(void);
void waitProc(void);
void waitProcInOrder(void);