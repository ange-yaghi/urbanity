#ifndef HELLO_WORLD_COMPILER_LANGUAGE_RULES_H
#define HELLO_WORLD_COMPILER_LANGUAGE_RULES_H

#include <piranha.h>

class LanguageRules : public piranha::LanguageRules {
public:
	LanguageRules();
	~LanguageRules();

	virtual void registerBuiltinNodeTypes();
};

#endif /* HELLO_WORLD_COMPILER_LANGUAGE_RULES_H */