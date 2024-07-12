#include "../headers/header.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void renderText(SDL_Renderer *renderer, const char *text, int x, int y, SDL_Color color, TTF_Font *font)
{
     SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
     if (surface == NULL)
     {
          return;
     }

     SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
     if (texture == NULL)
     {
          printf("Erreur de création de la texture : %s\n", SDL_GetError());
          SDL_FreeSurface(surface);
          return;
     }

     SDL_Rect destRect;
     destRect.x = x;
     destRect.y = y;
     destRect.w = surface->w;
     destRect.h = surface->h;

     SDL_RenderCopy(renderer, texture, NULL, &destRect);

     SDL_DestroyTexture(texture);
     SDL_FreeSurface(surface);
}

char *trimWhitespace(char *str)
{
     char *end;

     // Trim leading space
     while (isspace((unsigned char)*str))
          str++;

     if (*str == 0) // All spaces?
          return str;

     // Trim trailing space
     end = str + strlen(str) - 1;
     while (end > str && isspace((unsigned char)*end))
          end--;

     // Write new null terminator
     *(end + 1) = 0;

     return str;
}

char *trimNumber(char *str)
{
     while (isdigit((unsigned char)*str))
          str++;
     return str;
}

int connexion(SDL_Renderer *renderer, TTF_Font *font)
{
     char login[50] = {0};
     char password[50] = {0};
     int login_length = 0;
     int password_length = 0;
     int hide_password = 1;
     int entering_login = 1;

     SDL_Color white = {255, 255, 255, 255};

     int running = 1;
     while (running)
     {
          SDL_Event event;
          while (SDL_PollEvent(&event))
          {
               if (event.type == SDL_QUIT)
               {
                    return -1;
               }
               else if (event.type == SDL_KEYDOWN)
               {
                    if (event.key.keysym.sym == SDLK_RETURN)
                    {
                         running = 0;
                    }
                    else if (event.key.keysym.sym == SDLK_BACKSPACE)
                    {
                         if (entering_login)
                         {
                              if (login_length > 0)
                              {
                                   login[--login_length] = '\0';
                              }
                         }
                         else
                         {
                              if (password_length > 0)
                              {
                                   password[--password_length] = '\0';
                              }
                         }
                    }
                    else if (event.key.keysym.sym == SDLK_TAB)
                    {
                         entering_login = !entering_login;
                    }
               }
               else if (event.type == SDL_TEXTINPUT)
               {
                    if (entering_login)
                    {
                         if (login_length < sizeof(login) - 1)
                         {
                              strcat(login, trimNumber(event.text.text));
                              login_length++;
                         }
                    }
                    else
                    {
                         if (password_length < sizeof(password) - 1)
                         {
                              strcat(password, event.text.text);
                              password_length++;
                         }
                    }
               }
          }

          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
          SDL_RenderClear(renderer);

          renderText(renderer, "Veuillez entrer votre login:", 100, 100, white, font);
          renderText(renderer, login, 100, 150, white, font);

          renderText(renderer, "Veuillez entrer votre mot de passe:", 100, 200, white, font);
          char password_display[50];
          if (hide_password)
          {
               for (int i = 0; i < password_length; i++)
               {
                    password_display[i] = '*';
               }
               password_display[password_length] = '\0';
          }
          else
          {
               strcpy(password_display, password);
          }
          renderText(renderer, password_display, 100, 250, white, font);

          SDL_RenderPresent(renderer);
     }

     // Afficher le mot de passe pour le débogage
     printf("Login saisi : %s\n", login);
     printf("Mot de passe saisi : %s\n", password);

     // Nettoyer les espaces blancs et les chiffres
     char *trimmed_login = trimWhitespace(login);
     printf("Login nettoyé : %s\n", trimmed_login);

     // Validation du login et du mot de passe
     FILE *fichier = fopen(USER_FILE, "r");
     if (fichier == NULL)
     {
          return -1;
     }

     User userTemp;
     char chiffre[50];
     char dechiffre[50];

     while (fscanf(fichier, "%d %s %s %s %s %s %s", &userTemp.user_id, userTemp.nom, userTemp.prenom, userTemp.login, userTemp.telephone, userTemp.mot_de_passe, userTemp.role) == 7)
     {
          printf("Comparaison : %s == %s, %d\n", trimmed_login, userTemp.login, strcmp(trimmed_login, userTemp.login));
          if (strcmp(trimmed_login, userTemp.login) == 0)
          {
               strcpy(chiffre, password);
               strcpy(dechiffre, userTemp.mot_de_passe);

               chiffrerCesar(chiffre, 10);
               dechiffrerCesar(dechiffre, 10);

               if (strcmp(chiffre, userTemp.mot_de_passe) == 0)
               {
                    fclose(fichier);
                    if (strcmp(userTemp.role, "ADMIN") == 0)
                    {
                         return 0;
                    }
                    else if (strcmp(userTemp.role, "USER") == 0)
                    {
                         return 1;
                    }
                    else if (strcmp(userTemp.role, "USERBLOQUE") == 0)
                    {
                         return 2;
                    }
               }
               else
               {
                    fclose(fichier);
                    return -1;
               }
          }
     }

     fclose(fichier);
     return -1;
}

int main(int argc, char *argv[])
{
     if (SDL_Init(SDL_INIT_VIDEO) != 0)
     {
          printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
          return 1;
     }

     if (TTF_Init() != 0)
     {
          printf("Erreur d'initialisation de SDL_ttf: %s\n", TTF_GetError());
          SDL_Quit();
          return 1;
     }

     SDL_Window *window = SDL_CreateWindow("Menu Principal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
     if (!window)
     {
          printf("Erreur de création de la fenêtre: %s\n", SDL_GetError());
          TTF_Quit();
          SDL_Quit();
          return 1;
     }

     SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
     if (!renderer)
     {
          printf("Erreur de création du renderer: %s\n", SDL_GetError());
          SDL_DestroyWindow(window);
          TTF_Quit();
          SDL_Quit();
          return 1;
     }

     TTF_Font *font = TTF_OpenFont("Roboto-Regular.ttf", 20);
     if (!font)
     {
          printf("Erreur de chargement de la police: %s\n", TTF_GetError());
          SDL_DestroyRenderer(renderer);
          SDL_DestroyWindow(window);
          TTF_Quit();
          SDL_Quit();
          return 1;
     }

     SDL_Color white = {255, 255, 255, 255};

     // Démarrer la saisie de texte SDL
     SDL_StartTextInput();

     int running = 1;
     while (running)
     {
          SDL_Event event;
          while (SDL_PollEvent(&event))
          {
               if (event.type == SDL_QUIT)
               {
                    running = 0;
               }
               else if (event.type == SDL_KEYDOWN)
               {
                    if (event.key.keysym.sym == SDLK_1)
                    {
                         int role = connexion(renderer, font);
                         if (role == 0)
                         {
                              printf("Admin connecté\n");
                              afficherMenuAdmin(renderer, font);
                         }
                         else if (role == 1)
                         {
                              printf("Utilisateur connecté\n");
                              afficherMenuUser(renderer, font);
                         }
                         else if (role == 2)
                         {
                              printf("Vous êtes bloqué\n");
                         }
                         else
                         {
                              printf("\033[31mLogin ou mot de passe incorrect\033[0m\n");
                         }
                    }
                    else if (event.key.keysym.sym == SDLK_2)
                    {
                         running = 0;
                    }
               }
          }

          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
          SDL_RenderClear(renderer);

          renderText(renderer, "--- Menu Principal ---", 100, 50, white, font);
          renderText(renderer, "1. Connexion", 100, 100, white, font);
          renderText(renderer, "2. Quitter", 100, 150, white, font);
          renderText(renderer, "Choisissez une option: ", 100, 200, white, font);

          SDL_RenderPresent(renderer);
     }

     SDL_StopTextInput();

     TTF_CloseFont(font);
     SDL_DestroyRenderer(renderer);
     SDL_DestroyWindow(window);
     TTF_Quit();
     SDL_Quit();

     return 0;
}
