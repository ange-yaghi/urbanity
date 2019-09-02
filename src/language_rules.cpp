#include "../include/language_rules.h"

LanguageRules::LanguageRules() {
	/* void */
}

LanguageRules::~LanguageRules() {
	/* void */
}

void LanguageRules::registerBuiltinNodeTypes() {
	// Builtin Types ======================================
	registerBuiltinType<piranha::ChannelNode>(
		"int_channel", &piranha::FundamentalType::IntType);
	registerBuiltinType<piranha::ChannelNode>(
		"string_channel", &piranha::FundamentalType::StringType);

	// Literal types
	registerBuiltinType<piranha::DefaultLiteralIntNode>("literal_int");
	registerBuiltinType<piranha::DefaultLiteralStringNode>("literal_string");


	// Operator types
	registerBuiltinType<
		piranha::OperationNodeSpecialized<piranha::native_int, piranha::AddOperationNodeOutput>>("int_add");

	// Conversion types
	registerBuiltinType<piranha::StringToIntConversionNode>("string_to_int");

	// Literals ===========================================
	registerLiteralType(piranha::LITERAL_INT, "literal_int");
	registerLiteralType(piranha::LITERAL_STRING, "literal_string");

	// Operations =========================================
	registerOperator(
		{ piranha::IrBinaryOperator::ADD, &piranha::FundamentalType::IntType, &piranha::FundamentalType::IntType },
		"int_add"
	);

	// Conversions ========================================
	registerConversion({ &piranha::FundamentalType::StringType, &piranha::FundamentalType::IntType }, "string_to_int");
}