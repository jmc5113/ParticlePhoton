
class LedPattern {
    public:
    
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void GetLedColor(int led) = 0;
};