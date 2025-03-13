#include <fcgi_stdio.h>

int main() {
    while (FCGI_Accept() >= 0) {
        printf("Content-type: text/html\r\n\r\n");
        printf("<html>\n<head>\n<title>Hello World!</title>\n</head>\n<body>\n");
        printf("<h1>Hello, World!</h1>\n<hr>\n");
        printf("</body>\n</html>\n");
    }
    return 0;
}
