#include "app/AppManager.h"
#include "database/mysql/MySQLDatabase.h"

int main(int argc, char* argv[])
{
	AppManager app;

    DBConfig config;
    config.host = "127.0.0.1";
    config.port = 3306;
    config.database = "library";
    config.username = "root";
    config.password = "123";

    MySQLDatabase db(config);

    if (db.connect())
    {
        std::cout << "Connected successfully!" << std::endl;
        std::cout << db.serverVersion() << std::endl;

        db.disconnect();
    }
    else
    {
        std::cout << "Connect failed!" << std::endl;
    }

	return app.run(argc,argv);
}