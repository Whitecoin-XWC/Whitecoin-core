#include <graphene/chain/wallfacer_lock_balance_evaluator.hpp>
#include <graphene/chain/committee_member_object.hpp>
#include <graphene/chain/lockbalance_object.hpp>
namespace graphene {
	namespace chain {
		void_result wallfacer_lock_balance_evaluator::do_evaluate(const wallfacer_lock_balance_operation& o) {
			try {
				const database& d = db();
				const asset_object&   asset_type = o.lock_asset_id(d);
				// 			auto & iter = d.get_index_type<wallfacer_member_index>().indices().get<by_account>();
				// 			auto itr = iter.find(o.lock_balance_account);
				// 			FC_ASSERT(itr != iter.end(), "Dont have lock wallfacer account");
				optional<wallfacer_member_object> iter = d.get(o.lock_balance_account);
				FC_ASSERT(iter.valid(), "Dont have lock account");
				optional<account_object> account_iter = d.get(iter->wallfacer_member_account);
				FC_ASSERT(account_iter.valid() && 
						  account_iter->addr == o.lock_address && 
						  iter->wallfacer_member_account == o.lock_balance_account_id, "Address or Account is wrong");
				bool insufficient_balance = d.get_balance(o.lock_address, asset_type.id).amount >= o.lock_asset_amount;
				FC_ASSERT(insufficient_balance, "Lock balance fail because lock account own balance is not enough");

				return void_result();
			}FC_CAPTURE_AND_RETHROW((o))			
		}
		void_result wallfacer_lock_balance_evaluator::do_apply(const wallfacer_lock_balance_operation& o) {
			try {
				database& d = db();
				const asset_object&   asset_type = o.lock_asset_id(d);
				d.adjust_balance(o.lock_address, asset(-o.lock_asset_amount, o.lock_asset_id));
				d.adjust_wallfacer_lock_balance(o.lock_balance_account, asset(o.lock_asset_amount, o.lock_asset_id));
				//d.adjust_lock_balance(o.lockto_miner_account, o.lock_balance_account, o.lock_asset_amount);
				// 			auto & iter = d.get_index_type<wallfacer_member_index>().indices().get<by_account>();
				// 			auto itr = iter.find(o.lock_balance_account);
				//optional<wallfacer_member_object> iter = d.get(o.lock_balance_account);
				d.modify(d.get(o.lock_balance_account), [o, asset_type](wallfacer_member_object& b) {
					auto map_wallfacer_lockbalance_total = b.wallfacer_lock_balance.find(asset_type.symbol);
					if (map_wallfacer_lockbalance_total != b.wallfacer_lock_balance.end()) {
						map_wallfacer_lockbalance_total->second += asset(o.lock_asset_amount,o.lock_asset_id);
					}
					else {
						b.wallfacer_lock_balance[asset_type.symbol] = asset(o.lock_asset_amount,o.lock_asset_id);
					}
				});
				return void_result();
			}FC_CAPTURE_AND_RETHROW((o))			
		}
		void_result wallfacer_foreclose_balance_evaluator::do_evaluate(const wallfacer_foreclose_balance_operation& o) {
			try {
				const database& d = db();
				const asset_object&   asset_type = o.foreclose_asset_id(d);
				// 			auto & iter = d.get_index_type<wallfacer_member_index>().indices().get<by_account>();
				// 			auto itr = iter.find(o.lock_balance_account);
				// 			FC_ASSERT(itr != iter.end(), "Dont have lock wallfacer account");
				optional<wallfacer_member_object> iter = d.get(o.foreclose_balance_account);
				FC_ASSERT(iter.valid(), "Dont have lock account");
				optional<account_object> account_iter = d.get(iter->wallfacer_member_account);
				FC_ASSERT(account_iter.valid() && account_iter->addr == o.foreclose_address && o.foreclose_balance_account_id == iter->wallfacer_member_account, "Address is wrong");
				bool insufficient_balance = d.get_wallfacer_lock_balance(iter->id, asset_type.id).amount >= o.foreclose_asset_amount;
				FC_ASSERT(insufficient_balance, "Lock balance fail because lock account own balance is not enough");
			}FC_CAPTURE_AND_RETHROW((o))			
		}
		void_result wallfacer_foreclose_balance_evaluator::do_apply(const wallfacer_foreclose_balance_operation& o) {
			try {
				database& d = db();
				const asset_object&   asset_type = o.foreclose_asset_id(d);
				d.adjust_balance(o.foreclose_address, asset(o.foreclose_asset_amount,o.foreclose_asset_id));
				d.adjust_wallfacer_lock_balance(o.foreclose_balance_account, asset(-o.foreclose_asset_amount, o.foreclose_asset_id));
				//d.adjust_lock_balance(o.lockto_miner_account, o.lock_balance_account, o.lock_asset_amount);
				// 			auto & iter = d.get_index_type<wallfacer_member_index>().indices().get<by_account>();
				// 			auto itr = iter.find(o.lock_balance_account);
				//optional<wallfacer_member_object> iter = d.get(o.foreclose_balance_account);
				d.modify(d.get(o.foreclose_balance_account), [o, asset_type](wallfacer_member_object& b) {
					auto map_wallfacer_lockbalance_total = b.wallfacer_lock_balance.find(asset_type.symbol);
					if (map_wallfacer_lockbalance_total != b.wallfacer_lock_balance.end()) {
						map_wallfacer_lockbalance_total->second -= asset(o.foreclose_asset_amount,o.foreclose_asset_id);
					}

				});
				return void_result();
			}FC_CAPTURE_AND_RETHROW((o))			
		}

		void_result wallfacer_update_multi_account_evaluator::do_evaluate(const wallfacer_update_multi_account_operation& o)
		{
			try {
				const database& d = db();
				const auto& assets = d.get_index_type<asset_index>().indices().get<by_symbol>();
				FC_ASSERT(assets.find(o.chain_type)!=assets.end());
				FC_ASSERT(o.hot != o.cold);

				const auto& multi_assets = d.get_index_type<multisig_account_pair_index>().indices().get<by_multisig_account_pair>();
				auto multisig_account_obj = multi_assets.find(boost::make_tuple(o.hot,o.cold,o.chain_type));
				FC_ASSERT(multisig_account_obj != multi_assets.end());

				if (d.head_block_num() > XWC_CROSSCHAIN_ERC_FORK_HEIGHT) {
					int multi_wallfacer_size = 0;
					auto wallfacer_range = d.get_index_type<multisig_address_index>().indices().get<by_multisig_account_pair_id>().equal_range(multisig_account_obj->id);
					for (auto wallfacer : boost::make_iterator_range(wallfacer_range.first, wallfacer_range.second)) {
						multi_wallfacer_size += 1;
					}

					auto all_wallfacers = d.get_wallfacer_members();
					FC_ASSERT(multi_wallfacer_size == all_wallfacers.size(), "wallfacer size is not enough");
				}

				FC_ASSERT(multisig_account_obj->effective_block_num==0,"no need to update again.");

                //get the multi-asset,and make it get worked
			} FC_CAPTURE_AND_RETHROW((o))
		}

		void_result wallfacer_update_multi_account_evaluator::do_apply(const wallfacer_update_multi_account_operation& o)
		{
			try
			{
				//TODO
				//we need implemention
				database& d = db();
				//modify the data for the
				auto previous = d.get_current_multisig_account(o.chain_type);
				auto& multi_assets = d.get_index_type<multisig_account_pair_index>().indices().get<by_multisig_account_pair>();
				auto multisig_account_obj = multi_assets.find(boost::make_tuple(o.hot, o.cold, o.chain_type));
				auto head_num = d.head_block_num();
				if (previous.valid())
				{
					auto& p_obj = d.get_object(previous->id);
					d.modify(*(multisig_account_pair_object*)&p_obj, [o, head_num](multisig_account_pair_object& obj) {
						obj.end_block = head_num + 10;
					}
					);
				}
				
				d.modify(*multisig_account_obj, [o,head_num](multisig_account_pair_object& obj) {
					obj.effective_block_num = head_num + 10;
				});

				
				//multi_assets.modify();
			}FC_CAPTURE_AND_RETHROW((o))
		}

	}
}
