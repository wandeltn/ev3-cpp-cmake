#ifndef __WEB_COMPONENT_BASE_HPP__
#define __WEB_COMPONENT_BASE_HPP__

#include <string>
#include <vector>
#include <memory>

namespace finder::server::webComponents
{
    enum class WebComponentType
    {
        INPUT = 0,
        BUTTON = 1,
        TEXTAREA = 2,
        SELECT = 3,
        OPTION = 4,
        DIV = 5,
        SPAN = 6,
        H1 = 7,
        H2 = 8,
        H3 = 9,
        H4 = 10,
        H5 = 11,
        H6 = 12,
        P = 13,
        A = 14,
        IMG = 15,
        UL = 16,
        OL = 17,
        LI = 18,
        TABLE = 19,
        TR = 20,
        TD = 21,
        TH = 22,
        FORM = 23,
        LABEL = 24,
        IFRAME = 25,
        SCRIPT = 26,
        STYLE = 27,
        LINK = 28,
        META = 29,
        HEAD = 30,
        BODY = 31,
        HTML = 32,
};

    class WebComponentBase
    {
        public:
            WebComponentBase();
            virtual ~WebComponentBase() = default;

            virtual std::string render() = 0;
            virtual std::string getComponentName() = 0;
            virtual std::string getComponentType() = 0;
            virtual std::string getComponentHTML() = 0;

            void addChild(std::shared_ptr<WebComponentBase> child);
            void removeChild(std::shared_ptr<WebComponentBase> child);
            std::vector<std::shared_ptr<WebComponentBase>> getChildren();

        private:
            int id;
            static int idCounter;
            bool canHaveChildren;
            // the name of the component
            WebComponentType componentType;
            // not all components will have children (e.g. input, button, etc.)
            std::vector<std::shared_ptr<WebComponentBase>> children;
    };
} // namespace finder::server::webComponents

#endif // __WEB_COMPONENT_BASE_HPP__