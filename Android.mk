LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := impelog
LOCAL_CFLAGS := -w -s -Wno-error=format-security -fvisibility=hidden -fpermissive -fexceptions
LOCAL_CPPFLAGS := -w -s -Wno-error=format-security -fvisibility=hidden -Werror -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fpermissive -Wall -fexceptions
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all,-llog
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2
LOCAL_ARM_MODE := arm
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Menushka/ImGui
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Menushka/ImGui/backends
LOCAL_SRC_FILES := Main.cpp \ Menushka/ImGui/imgui.cpp \ Menushka/ImGui/imgui_draw.cpp \ Menushka/ImGui/imgui_demo.cpp \ Menushka/ImGui/imgui_widgets.cpp \ Menushka/ImGui/imgui_tables.cpp \ Menushka/ImGui/backends/imgui_impl_opengl3.cpp \ Menushka/ImGui/backends/imgui_impl_android.cpp \ Includes/Fake_dlfcn.cpp \ Includes/Utils.h \ Includes/oxorany.cpp \ Menushka/And64InlineHook.cpp
include $(BUILD_SHARED_LIBRARY)
