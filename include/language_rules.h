#ifndef LANGUAGE_RULES_H
#define LANGUAGE_RULES_H

#include <piranha.h>

class LanguageRules : public piranha::LanguageRules {
public:
	LanguageRules();
	~LanguageRules();

	virtual void registerBuiltinNodeTypes();
};

#endif /* LANGUAGE_RULES_H */
