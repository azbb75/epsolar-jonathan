Import("env")
from shutil import copyfile
import subprocess
import gzip
import io

def write_gzip(file_path):
    in_file = open(file_path, 'rb')
    out_file = gzip.open(file_path + ".gz", 'wb')
    for line in in_file.readlines():
        out_file.write(line)
    in_file.close()
    out_file.close()

def pre_build_fs_hook(source, target, env):
    print "Running pre_build_fs_hook"
    print "Running gulp"
    p = subprocess.Popen('cd web && npm install && gulp', shell=True, stdout=subprocess.PIPE)
    stdout, stderr = p.communicate()
    #TODO: Make this output realtime
    for line in stdout.splitlines():  
        line = line.rstrip()  
        print line
    
    rawHtml = './web/dist/index.html'
    write_gzip(rawHtml)
    compressedHtml = rawHtml + '.gz'
    finalHtml = './data/index.html.gz'
    print "Copying %s to %s"%(compressedHtml, finalHtml)
    copyfile(compressedHtml, finalHtml)
    print "Successfully completed before_fs_upload hook"
    # do some actions

env.AddPreAction("$BUILD_DIR/spiffs.bin", pre_build_fs_hook)