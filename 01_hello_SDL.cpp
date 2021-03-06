/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include<SDL2/SDL.h>
#include <stdio.h>

//параметры окна
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// включить SDL и сделать окно
bool init();

//загрузка медиа (рисунок)
bool loadMedia();

// все закрыть
void close();

//окно, которое мы показываем
SDL_Window* gWindow = NULL;

// поверхность в окне
SDL_Surface* gScreenSurface = NULL;

SDL_Renderer* renderer = NULL;

//*p == NULL;

bool init()
{
//инициализация флага (?) что это такое?
    bool success = true;
//инициализация SDL

    // если SDL_Init c SDL_INIT VIDEO в качестве параметра меньше нуля,
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        // все плохо, установить false в success
        success = false;
    } else {
        // в противном случае создаем окно
// gWindow (переменная, внутри которой указатель(?) на место, по которому лежит окно в памяти) приравнена к функции SDL_CreateWindow, которая должна создать окно (?)
           gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        // если указатель равен NULL,
           // SDL_CreateWindowAndRenderer( SCREEN_WIDTH,SCREEN_HEIGHT , 0, &gWindow, &renderer);
        if( gWindow == NULL ) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
// все плохо, устанавливаем false
            success = false;
        } else {
            //в противном случае устанавливаем поверхность окна
            // переменная gScreenSurface (в которой указатель на поверхность окна в памяти (?)) приравнена к функции SDL_GetWindowSurface, у котоой в качестве параметра переменная gWindow, где теперь лежит адрес нашено окна (?)
               gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }
    // возвращаем "успех" (возвращаем куда? куда попадает "уведомление", что все прошло успешно?)
    return success;
}


Uint32 getpixel( SDL_Surface *surface, int x, int y) {

    SDL_LockSurface(gScreenSurface);

    int bpp =  gScreenSurface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)gScreenSurface->pixels + y *  gScreenSurface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
    SDL_UnlockSurface(gScreenSurface);
}

void DrawPixel(SDL_Surface *screen, int x, int y,
               Uint8 R, Uint8 G, Uint8 B)
{
    Uint32 color = SDL_MapRGB(screen->format, R, G, B);
    switch (screen->format->BytesPerPixel)
    {
    case 1: // Используем 8-bpp (бит на пиксель)
    {
        Uint8 *bufp = (Uint8 *)screen->pixels +
            /* pixels – указатель на начало области данных,
               описывающей состояние пикселей поверхности screen */
            y*screen->pitch + x;
        /* pitch – количество байт, занимаемых данными
           о пикселях одной строки */      *bufp = color;
    }
    break;
    case 2: // Возможно 15-bpp или 16-bpp
    {
        Uint16 *bufp = (Uint16 *)screen->pixels +
            y*screen->pitch/2 + x;
        /* Поскольку (Uint16 *)screen->pixels возвращает
      указатель на целое число, занимающее в памяти 2 байта,
      при вычислении смещения делим длину строки в байтах
      на 2 */
        *bufp = color;
    }
    break;
    case 3: // Медленный режим 24-bpp, обычно не применяется
    {
        Uint8 *bufp = (Uint8 *)screen->pixels +
            y*screen->pitch + x * 3;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
        { /* Учет возможного различия в порядке следования байт
             в машинном слове различных процессорных архитектур */
            bufp[0] = color;
            bufp[1] = color >> 8;
            bufp[2] = color >> 16;
        } else {
            bufp[2] = color;
            bufp[1] = color >> 8;
            bufp[0] = color >> 16;
        }
    }
    break;
    case 4: // Возможно 32-bpp...
    {
        Uint32 *bufp = (Uint32 *)screen->pixels +
            y*screen->pitch/4 + x;
        /* Поскольку (Uint32 *)screen->pixels возвращает
      указатель на целое число, занимающее в памяти 4 байта,
      при вычислении смещения делим длину строки в байтах
      на 4 */
        *bufp = color;
    }
    break;
    }
}


bool loadMedia()
{
    //устанавливаем флаг
    bool success = true;
//пробуем загрузить рисунок
    getpixel( gScreenSurface, 50,100);
    // если указатель в  gHelloWorld рaвен нулю,
    //  if( *p == NULL ) {
    //       printf( "Что-то не так с пикселем! SDL Error: %s\n", "~/Desktop/make/hello_world.bmp", SDL_GetError() );
    //      success = false;
    //  }
    DrawPixel (gScreenSurface, 50, 100, 0, 255, 0);


    return success;
}

void close()
{
//зачистка изображение -
    // берем функцию  SDL_FreeSurface с параметром gHelloWorld (зачем?) и говорим, что gHelloWorld снова равен NULL
    // SDL_FreeSurface(pixel);
    // pixel  = NULL;

    // SDL_RenderClear( renderer );
    // renderer = NULL;
//уничтожаем окно
    //в общем, аналогично
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
//выход из библиотеки (?)
    SDL_Quit();
}

int main( int argc, char* args[] )
{

    //включаем SDL и создаем окно
    // не знаю, что означает ! перед функциями, подозреваю, что так мы говорим "если функция такая-то не сработала",
    if( !init() ) {
        // печатаем сообщение об ошибке
        printf( "Failed to initialize!\n" );
    } else {
//если окно создалось, то грузим изображение
        if( !loadMedia() ) {
            // если изображение загрузить не удалось, пишем соответствующее сообщение об ошибке
            printf( "Failed to load media!\n" );
        } else {
            //добавляем изображение. Что тут с аргументами пока что не понимаю.
            // SDL_BlitSurface( gHelloWorld , NULL, gScreenSurface, NULL );
            //обновляем изображение
             SDL_UpdateWindowSurface( gWindow );

            //ждем пару секунд
            SDL_Delay( 5000 );

        }
    }
    // закрываем все
        close();
// возвращаем 0 операционной системе как знак успеха (?)
        return 0;
    }
