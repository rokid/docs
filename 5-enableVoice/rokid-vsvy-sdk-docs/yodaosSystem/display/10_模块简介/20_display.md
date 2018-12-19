DFBWindowID createWindow(shared_ptr<Caps>& desc);

    DFBWindowID : int

    desc = {
        int x,
        int y,
        int width,
        int height,
        DisplayDevice::DisplayType deviceType,
    }

void destroyWindow(DFBWindowID windowID, DisplayDevice::DisplayType deviceType = DisplayDevice::DisplayType::DISPLAY_PRIMARY);

DFBTaskID draw(DFBWindowID windowID, shared_ptr<Caps>& cmd);

    DFBTaskID : int

    cmd所有对象成员均为caps类型，每个子对象代表一条绘制指令
    cmd = {
        {
            ElementType type = ELEMENT_IMAGE,
            char *url,
            ImageLayout layout,
        },
        {
            ElementType type = ELEMENT_STRING,
            char *text,
            StringLayout layout,
            int x,
            int y,
            int fontSize,
            Color color = 0xffffffff,
            string font,
        }
    }
    Color : uint32_t

void getFBinfo(shared_ptr<Caps>& info);

    info = {
        {
            DisplayDevice::DisplayType displayType = DisplayDevice::DisplayType::DISPLAY_PRIMARY,
            int width,
            int height,
        }
    }