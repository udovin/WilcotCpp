/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/io/IStream.h>

namespace wilcot { namespace io {

const IStream::Mode IStream::NOT_OPEN = 0;

const IStream::Mode IStream::READ = 1;

const IStream::Mode IStream::WRITE = 2;

IStream::~IStream() {}

}}
