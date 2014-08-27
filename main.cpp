#ifdef STATIC
#include <QtPlugin>
Q_IMPORT_PLUGIN(qsvg)
#endif

#include <QtGui/QApplication>
#include <iostream>
#include "VerySeriousSetup.h"
#include "hidapi.h"
#include "vsbprog.h"
#include "keyseq.h"

class MyApplication
    : public QApplication
{
public:
    MyApplication(int& argc, char** argv);
    virtual bool notify(QObject* receiver, QEvent* event);
};

MyApplication::MyApplication(int& argc, char** argv)
    : QApplication(argc, argv)
{}

bool MyApplication::notify(QObject* receiver, QEvent* event)
{
    bool done = true;
    try
    {
        done = QApplication::notify(receiver, event);
    }
    catch(VsbError err)
    {
        std::cerr << "Unhandled VsbError: " << err.what() << std::endl;
    }
    catch(InvalidKeycode err)
    {
        std::cerr << "Unhandled InvalidKeycode: " << err.what() << std::endl;
    }
    catch(InvalidModName err)
    {
        std::cerr << "Unhandled InvalidModName: " << err.what() << std::endl;
    }
    catch(InvalidKeyName err)
    {
        std::cerr << "Unhandled InvalidKeyname: " << err.what() << std::endl;
    }
    catch(const std::exception& ex)
    {
        std::cerr << "Unhandled exception: " << ex.what() << std::endl;
    }
    return done;
}

int main(int argc, char** argv)
{
    hid_init();
    MyApplication app(argc, argv);
    Q_INIT_RESOURCE(images);
    VssMainWindow foo;
    foo.show();
    return app.exec();
}
