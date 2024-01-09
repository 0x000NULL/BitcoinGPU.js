#ifndef LIBBITCOIN_BITCOIN_H
#define LIBBITCOIN_BITCOIN_H

/**
 * @mainpage libbitcoin API dox
 *
 * @section intro_sec Introduction
 *
 * libbitcoin is a bitcoin library targeted towards high end use.
 * The library places a heavy focus around asychronicity. This enables a
 * big scope for future scalability as each component has its own
 * thread pool. By increasing the number of threads for that component
 * the library is able to scale outwards across CPU cores. This will be
 * vital in the future as the demands of the bitcoin network grow.
 *
 * Another core design principle is libbitcoin is not a framework, but
 * a toolkit. Frameworks hinder development during the latter stages of
 * a development cycle, enforce one style of coding and do not work well
 * with other frameworks. By contrast, we have gone to great pains to make
 * libbitcoin function as an independent set of mutual components with no
 * dependencies between them.
 *
 * @section overview_sec Overview
 *
 * Broadly speaking the main services in libbitcoin can be divided down
 * three lines.
 *
 * @subsection network Network services
 *
 * These services are concerned with the network side of things.
 *
 * - @link libbitcoin::channel channel @endlink
 * - @link libbitcoin::network network @endlink
 * - @link libbitcoin::protocol protocol @endlink
 * - @link libbitcoin::hosts hosts @endlink
 * - @link libbitcoin::handshake handshake @endlink
 *
 * @subsection blockchain Blockchain service
 *
 * Bitcoin's blockchain is usually disk oriented. Backends all implement
 * the blockchain allowing programs to utilise backends using the same
 * code.
 *
 * - @link libbitcoin::blockchain blockchain @endlink (abstract interface
     for blockchain backends)
 * - @link libbitcoin::bdb_blockchain bdb_blockchain @endlink
 *
 * @subsection supporting Supporting services
 *
 * These services utilise other services and provide additional
 * functionality. They can be thought of as composed services.
 *
 * - @link libbitcoin::poller poller @endlink
 * - @link libbitcoin::transaction_pool transaction_pool @endlink
 * - @link libbitcoin::session session @endlink
 *
 * @section message Message
 *
 * libbitcoin operates around messages. Each message corresponds to
 * one of the packets in the bitcoin network protocol.
 *
 * These primitives make up the corpus of libbitcoin.
 *
 * - @link libbitcoin::message::version message::version @endlink
 * - @link libbitcoin::message::verack message::verack @endlink
 * - @link libbitcoin::message::address message::address @endlink
 * - @link libbitcoin::message::inventory message::inventory @endlink
 * - @link libbitcoin::message::get_data message::get_data @endlink
 * - @link libbitcoin::message::get_blocks message::get_blocks @endlink
 * - @link libbitcoin::message::transaction message::transaction @endlink
 * - @link libbitcoin::message::block message::block @endlink
 * - @link libbitcoin::message::get_address message::get_address @endlink
 * - @link libbitcoin::message::ping message::ping @endlink
 *
 * @section base Foundational
 *
 * These classes provide foundational functionality that is widely used.
 *
 * - @link libbitcoin::serializer serializer @endlink /
 *   @link libbitcoin::deserializer deserializer @endlink
 * - @link libbitcoin::script script @endlink
 * - @link libbitcoin::payment_address payment_address @endlink
 * - @link libbitcoin::elliptic_curve_key elliptic_curve_key @endlink
 * - @link libbitcoin::big_number big_number @endlink
 * - @link libbitcoin::async_service async_service @endlink
 *
 * @section useful-funcs Useful functions
 *
 * In accordance with C++ principles of encapsulation, operations which
 * wrap or compose other operations are not provided as member functions,
 * but as free functions.
 *
 * This minimises intrusion of class interfaces and provides a clear
 * separation as a matter of API design choice.
 *
 * @subsection transaction Transaction
 *
 * - @link libbitcoin::hash_transaction hash_transaction @endlink
 * - @link libbitcoin::generate_merkle_root generate_merkle_root @endlink
 * - @link libbitcoin::previous_output_is_null previous_output_is_null @endlink
 * - @link libbitcoin::is_coinbase is_coinbase @endlink
 * - @link libbitcoin::total_output_value total_output_value @endlink
 *
 * @subsection block Block
 *
 * - @link libbitcoin::hash_block_header hash_block_header @endlink
 * - @link libbitcoin::block_value block_value @endlink
 * - @link libbitcoin::block_work block_work @endlink
 * - @link libbitcoin::block_locator_indices block_locator_indices @endlink
 * - @link libbitcoin::genesis_block genesis_block @endlink
 *
 * @subsection blockchain Blockchain
 *
 * - @link libbitcoin::fetch_block fetch_block @endlink
 *
 * @subsection format Format
 *
 * - @link libbitcoin::pretty_hex pretty_hex @endlink
 * - @link libbitcoin::bytes_from_pretty bytes_from_pretty @endlink
 * - @link libbitcoin::hash_from_pretty hash_from_pretty @endlink
 * - @link libbitcoin::extend_data extend_data @endlink
 * - @link libbitcoin::cast_chunk cast_chunk @endlink
 * - @link libbitcoin::uncast_chunk uncast_chunk @endlink
 *
 * @subsection hashing Hashing
 *
 * - @link libbitcoin::generate_ripemd_hash generate_ripemd_hash @endlink
 * - @link libbitcoin::generate_sha256_hash generate_sha256_hash @endlink
 * - @link libbitcoin::generate_sha256_checksum generate_sha256_checksum @endlink
 *
 * @subsection base58 Base58
 *
 * - @link libbitcoin::encode_base58 encode_base58 @endlink
 * - @link libbitcoin::decode_base58 decode_base58 @endlink
 */

// Convenience header that includes everything
// Not to be used internally. For API users.
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/error.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/address.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/network/channel.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/network/shared_const_buffer.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/network/network.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/network/hosts.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/network/handshake.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/block.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/session.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/poller.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/format.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/validate.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/constants.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/getx_responder.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/types.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/messages.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/blockchain/organizer.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/blockchain/blockchain.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/utility/elliptic_curve_key.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/utility/assert.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/utility/ripemd.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/utility/logger.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/utility/sha256.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/utility/base58.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/utility/big_number.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/utility/serializer.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/utility/subscriber.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/utility/weak_bind.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/utility/key_formats.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/script.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/transaction.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/network/protocol.hpp>
#include <C:\Users\e.aldrich\Desktop\BitcoinGPU.js\test at self written\bitcoin/async_service.hpp>
#ifdef BDB_ENABLED
    #include <bitcoin/blockchain/bdb_blockchain.hpp>
#endif
#ifdef KYOTO_ENABLED
    #include <bitcoin/blockchain/kyoto_blockchain.hpp>
#endif

namespace bc = libbitcoin;

#endif

