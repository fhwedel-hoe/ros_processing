#include <vector>
#include <iostream>

#include "submodules/TypedJNI/typedjni.hpp"

int main(int, char**) {
    JavaVMInitArgs vm_args;
    std::vector<JavaVMOption> options;
    JavaVMOption jvmo;
    jvmo.optionString = (char *)"-Djava.class.path=processing/application.linux64/lib/processing.jar"; options.push_back(jvmo);
    vm_args.options = options.data();
    vm_args.nOptions = options.size();
    vm_args.version = JNI_VERSION_1_8;
    TypedJNIEnv env(vm_args);
    auto pwcls = env.find_class("processing$Worker");
    auto constructor = pwcls.GetConstructor<jobject>("(Lprocessing;)V");
    auto pwobj = constructor(NULL);
    auto processInput = pwobj.GetMethod<void(jfloat)>("processInput");
    auto getState = pwobj.GetMethod<jfloat()>("getState");
    float f;
    std::cout << "Bitte eine Zahl eingeben: " << std::flush;
    std::cin >> f;
    processInput(f);
    std::cout << getState() << std::endl;
    return 0;
}
