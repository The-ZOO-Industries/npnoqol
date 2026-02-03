#include "UUID.h"

UUID_J::UUID_J(const jobject instance)
	: JavaClass(instance)
{

}

UUID_J::~UUID_J() = default;

jint UUID_J::Version() const
{
	return maps::UUID(this->instance).version.call();
}

jstring UUID_J::ToString() const
{
	return (jstring)jobject(maps::UUID(this->instance).toString.call());
}