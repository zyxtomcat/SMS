#SConscript(['test/SConstruct'])
            
import os

env = Environment()
debug = ARGUMENTS.get('debug', 0) 
if int(debug) == 1:
    env.Append(CCFLAGS = '-g3')

env.Append(CCFLAGS = '-Wall')
env.Append(CPPPATH = ['.', '..','../public', '/usr/local/mapgoo/include'])
env.Append(LIBPATH=['/usr/local/lib', '/usr/lib64', '/usr/local/mapgoo/lib'])
env.Append(RPATH=['/usr/local/lib', '/usr/local/lib64', '/usr/lib64', '/usr/local/mapgoo/lib'])
env.Append(LIBS=['Ice', 'IceUtil', 'jsoncpp', 'mapgoobase', 'crypto', 'mysqlcppconn'])

sasdtest = env.Program('sasdtest', [
                                            'test.cpp', 
                                            '../SAS.cpp',
                                            '../public/PublicFunction.cpp'
                                            ])


