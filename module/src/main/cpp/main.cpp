#include <cstring>
#include <unistd.h>
#include <cinttypes>
#include <thread>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <jni.h>
#include "zygisk.hpp"
#include "hook.h"

using zygisk::Api;
using zygisk::AppSpecializeArgs;
using zygisk::ServerSpecializeArgs;
class MyModule : public zygisk::ModuleBase {
public:
    void onLoad(Api *api, JNIEnv *env) override {
        env_ = env;
        this->api = api;
        // this->env = env;
    }

    void preAppSpecialize(AppSpecializeArgs *args) override {
        if (!args || !args->nice_name) {
            LOGE("Skip unknown process");
            return;
        }
        /*
        enable_hack = isGame(env_, args->app_data_dir);
        auto dumpGame = env->GetStringUTFChars(args->nice_name, nullptr);
        auto dumpDataDir = env->GetStringUTFChars(args->app_data_dir, nullptr);
        preSpecialize(dumpGame, dumpDataDir);
        env->ReleaseStringUTFChars(nice_name, dumpGame);
        env->ReleaseStringUTFChars(app_data_dir, dumpDataDir);
        */
    }

    void postAppSpecialize(const AppSpecializeArgs *) override {
        if (enable_hack) {
            int ret;
            pthread_t ntid;
            if ((ret = pthread_create(&ntid, nullptr, hack_thread, nullptr))) {
                LOGE("can't create thread: %s\n", strerror(ret));
            }
        }
    }

private:
    JNIEnv *env_{};
    JNIEnv *env;
    bool enableDump;
    char *dumpGameDataDir;
    /*
    preSpecialize(const char *dumpGame, const char *dumpDataDir) {
        if (strcmp(dumpGame = GamePackageName) == 0) {
            enableDump = true;
            dumpGameDataDir = new char[strlen(dumpDataDir) +1];
            strcpy(dumpGameDataDir, dumpDataDir);
        }
    }
    */
};

REGISTER_ZYGISK_MODULE(MyModule)