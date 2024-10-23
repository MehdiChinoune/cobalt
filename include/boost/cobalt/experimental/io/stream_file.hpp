//
// Copyright (c) 2024 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_COBALT_EXPERIMENTAL_IO_STREAM_FILE_HPP
#define BOOST_COBALT_EXPERIMENTAL_IO_STREAM_FILE_HPP

#include <boost/asio/basic_stream_file.hpp>
#if defined(BOOST_ASIO_HAS_FILE)

#include <boost/cobalt/config.hpp>
#include <boost/cobalt/experimental/io/buffer.hpp>
#include <boost/cobalt/experimental/io/file.hpp>
#include <boost/cobalt/experimental/io/ops.hpp>
#include <boost/cobalt/op.hpp>

#include <boost/system/result.hpp>

namespace boost::cobalt::experimental::io
{


struct stream_file : file
{
  using native_handle_type = asio::basic_stream_file<executor>::native_handle_type;

  BOOST_COBALT_DECL stream_file(const cobalt::executor & executor = this_thread::get_executor());
  BOOST_COBALT_DECL stream_file(const char * path, file_base::flags open_flags,
                                const cobalt::executor & executor = this_thread::get_executor());
  BOOST_COBALT_DECL stream_file(const std::string & path, file_base::flags open_flags,
                                const cobalt::executor & executor = this_thread::get_executor());
  BOOST_COBALT_DECL stream_file(const native_handle_type & native_file,
                                const cobalt::executor & executor = this_thread::get_executor());
  BOOST_COBALT_DECL stream_file(stream_file && sf) noexcept;

  write_op write_some(const_buffer_sequence buffer)
  {
    return {buffer, this, initiate_write_some_};
  }
  read_op read_some(mutable_buffer_sequence buffer)
  {
    return {buffer, this, initiate_read_some_};
  }
  BOOST_COBALT_DECL system::result<void> resize(std::uint64_t n);

  BOOST_COBALT_DECL system::result<std::uint64_t> seek(
      std::int64_t offset,
      seek_basis whence);

 private:
  BOOST_COBALT_DECL static void initiate_read_some_(void *, mutable_buffer_sequence, boost::cobalt::completion_handler<boost::system::error_code, std::size_t>);
  BOOST_COBALT_DECL static void initiate_write_some_(void *, const_buffer_sequence, boost::cobalt::completion_handler<boost::system::error_code, std::size_t>);


  asio::basic_stream_file<executor> implementation_;

};


}

#endif
#endif //BOOST_COBALT_EXPERIMENTAL_IO_STREAM_FILE_HPP
