#include <node.h>
#include "omp.h"
#include <string>

namespace demo{
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::String;
    using v8::Value;
    using v8::Number;
    using v8::Exception;
    using v8::Array;
    using v8::Integer;

    
    void Method(const FunctionCallbackInfo<Value>& args){
        Isolate* isolate = args.GetIsolate();
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
    }

    void Add(const FunctionCallbackInfo<Value>& args){
        Isolate* isolate = args.GetIsolate();
        if(args.Length() < 2){
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")
            ));
            return;
        }
        if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }
        double value = args[0]->NumberValue() + args[1]->NumberValue();
        Local<Number> num = Number::New(isolate, value);
        args.GetReturnValue().Set(num);
    }

    void Factoral(const FunctionCallbackInfo<Value>& args){
        Isolate* isolate = args.GetIsolate();
        if(args.Length() < 1){
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")
            ));
            return;
        }

        if (!args[0]->IsNumber()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }

        int number = args[0]->NumberValue();
        int value = 0;

        for(int i = 1; i <= number; i++){
            value += i;
        }
        
        Local<Number> toReturn = Number::New(isolate, value);
        args.GetReturnValue().Set(toReturn);
    }

    void Parallel(const FunctionCallbackInfo<Value>& args){
        Isolate* isolate = args.GetIsolate();
        Local<Array> results = Array::New(isolate, 4);
        #pragma omp parallel
        {
            int index = omp_get_thread_num();
            Local<Number> a = Number::New(isolate, (index + index) * index);
            results->Set(index,a); 
        }
        args.GetReturnValue().Set(results);
    }
    
    void init(Local<Object> exports){
        NODE_SET_METHOD(exports, "hello", Method);
        NODE_SET_METHOD(exports, "add", Add);
        NODE_SET_METHOD(exports, "parallel", Parallel);
        NODE_SET_METHOD(exports, "factoral", Factoral);
    }

    NODE_MODULE(addon, init)
}