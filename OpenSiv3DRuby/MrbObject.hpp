#pragma once

#include <Siv3D.hpp>
#include "mruby.h"
#include "mruby/class.h"
#include "mruby/data.h"

//----------------------------------------------------------
namespace siv3druby {

//----------------------------------------------------------

template <class T>
class MrbObject
{
public:
    static void Init(mrb_state *mrb, std::string name)
    {
        fInner.init(mrb, name);
    }

    static struct RClass* Cc()
    {
        return fInner.cc();
    }

    static void Initialize(mrb_value self, T *ptr)
    {
        fInner.initialize(self, ptr);
    }

    static mrb_value ToMrb(mrb_state *mrb, T *ptr)
    {
        return fInner.toMrb(mrb, ptr);
    }

    static T* ToCpp(mrb_state *mrb, mrb_value value)
    {
        return fInner.toCpp(mrb, value);
    }

    static struct mrb_data_type* DataType()
    {
        return fInner.dataType();
    }

    static bool IsInstance(mrb_state *mrb, mrb_value value)
    {
        return fInner.isInstance(mrb, value);
    }

protected:
    static T& Self(mrb_value value)
    {
        return fInner.self(value);
    }

    class Inner
    {
    public:
        void init(mrb_state *mrb, std::string name)
        {
            mName = name;

            mClass = mrb_define_class(mrb, mName.c_str(), mrb->object_class);
            MRB_SET_INSTANCE_TT(mClass, MRB_TT_DATA);

            mDataName = "siv3d_" + mName;
            mDataType = { mDataName.c_str(), free };
        }

        struct RClass* cc()
        {
            return mClass;
        }

        void initialize(mrb_value self, T *ptr)
        {
            mrb_data_init(self, ptr, dataType());
        }

        mrb_value toMrb(mrb_state *mrb, T *ptr)
        {
            struct RData *data = mrb_data_object_alloc(mrb, mClass, ptr, &mDataType);
            return mrb_obj_value(data);
        }

        T* toCpp(mrb_state *mrb, mrb_value value)
        {
            if (!isInstance(mrb, value)) {
                mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
            }

            return static_cast<T*>(DATA_PTR(value));
        }

        T& self(mrb_value value)
        {
            return *((T*)DATA_PTR(value));
        }

        struct mrb_data_type* dataType()
        {
            return &mDataType;
        }

        bool isInstance(mrb_state *mrb, mrb_value value)
        {
            return mrb_obj_is_instance_of(mrb, value, mClass);
        }

    private:
        static void free(mrb_state *mrb, void *p)
        {
            if (p) {
                delete ((T*)p);
            }
        }

        std::string mName;
        std::string mDataName;
        struct RClass *mClass;
        struct mrb_data_type mDataType;
    };

    static Inner fInner;
};
}
