class State
{
public:
    virtual void RenderLCD() = 0;
    virtual void RenderOLED() = 0;
    virtual void ExecuteMD() = 0;
};