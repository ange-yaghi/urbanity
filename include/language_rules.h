#ifndef URBANITY_LANGUAGE_RULES_H
#define URBANITY_LANGUAGE_RULES_H

#include <piranha.h>

class LanguageRules : public piranha::LanguageRules {
public:
	LanguageRules();
	~LanguageRules();

	virtual void registerBuiltinNodeTypes();
};

#endif /* URBANITY_LANGUAGE_RULES_H */
