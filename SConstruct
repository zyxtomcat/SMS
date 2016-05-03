SConscript(['test/SConstruct'])
            
import os
output = os.popen("slice2cpp --underscore -I/usr/share/slice -I./slice/ slice/SAS.ice").read()


env = Environment()
debug = ARGUMENTS.get('debug', 0) 
if int(debug) == 1:
    env.Append(CCFLAGS = '-g3')

env.Append(CCFLAGS = '-Wall')
env.Append(CPPPATH = ['.', './public', './CMPP', './Models/DAO', './Models/Entity', './Models/Service', './ISMG', './serial', './network','/usr/local/mapgoo/include'])
env.Append(LIBPATH=['/usr/local/lib', '/usr/lib64', '/usr/local/mapgoo/lib'])
env.Append(RPATH=['/usr/local/lib', '/usr/local/lib64', '/usr/lib64', '/usr/local/mapgoo/lib'])
env.Append(LIBS=['Ice', 'IceUtil', 'IceGrid', 'mapgoobase', 'jsoncpp', 'mysqlcppconn', 'crypto', 'event'])

sasdlib = env.SharedLibrary('sasd', [
                                        Glob('*.cpp'),
                                        Glob('./public/*.cpp'), 
                                        Glob('./serial/*.cpp'),
                                        Glob('./CMPP/*.cpp'), 
                                        Glob('./ISMG/*.cpp'),
                                        Glob('./network/*.cpp'),
                                        Glob('./Models/DAO/*.cpp'),
                                        Glob('./Models/Entity/*.cpp'),
                                        Glob('./Models/Service/*.cpp')
                                    ]
                            )

output = os.popen("mkdir -p /usr/local/mapgoo/lib").read()
env.Alias('install', env.Install('/usr/local/mapgoo/lib', sasdlib))

output = os.popen("mkdir -p /usr/local/mapgoo/sasd").read()
env.Alias('install', env.Install('/usr/local/mapgoo/sasd', 'sasd.conf'))
#env.Alias('install', env.Install('/etc/init.d', 'sasd'))
env.Alias('install', os.popen("chmod 755 /etc/init.d/sasd").read())
