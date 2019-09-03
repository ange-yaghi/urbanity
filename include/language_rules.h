#ifndef URBANITY_LANGUAGE_RULES_H
#define URBANITY_LANGUAGE_RULES_H

#include <piranha.h>

namespace urb {

    class LanguageRules : public piranha::LanguageRules {
    public:
        LanguageRules();
        ~LanguageRules();

        virtual void registerBuiltinNodeTypes();
    };

} /* namespace urb */

#endif /* URBANITY_LANGUAGE_RULES_H */
